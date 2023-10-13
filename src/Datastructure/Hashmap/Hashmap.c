#include "Hashmap.h"

#include <stdio.h>
#include <stdlib.h>

typedef char bool;
#define true 1
#define false 0

typedef struct HashmapEntryType {
    int key;
    void *value;
    HashmapEntry *next;
    bool isOccupied;
} HashmapEntry;

struct HashmapType {
    HashmapEntry *entries;
    HashmapEntry *linked;
    HashmapEntry *finalLinked;
    int size;
    int capacity;
};

Hashmap *Hashmap_New(int size) {
    Hashmap *hashmap = (Hashmap *)calloc(size, sizeof(Hashmap));
    hashmap->size = size;
    return hashmap;
}

void Hashmap_TearDown(Hashmap *hashmap) {
    Hashmap_Clear(hashmap);
    free(hashmap);
}

inline int GetHashKey(Hashmap *hashmap, int key) {
    return key % hashmap->size;
}

// O(1)
inline void AddToExistLinked(Hashmap *hashmap, HashmapEntry *entry) {
    HashmapEntry *linked = hashmap->linked;
    if (linked == NULL) {
        hashmap->linked = entry;
        hashmap->finalLinked = entry;
        return;
    } else {
        hashmap->finalLinked->next = entry;
        hashmap->finalLinked = entry;
    }
}

inline void RemoveFromExistLinked(Hashmap *hashmap, HashmapEntry *entry) {
    HashmapEntry *linked = hashmap->linked;
    if (linked == NULL) {
        return;
    }

    if (linked == entry) {
        hashmap->linked = NULL;
        hashmap->finalLinked = NULL;
        return;
    }

    HashmapEntry *last = linked;
    linked = linked->next;
    while(linked != NULL) {
        if (linked == entry) {
            last->next = linked;
            return;
        }
    }
}

inline HashmapEntry *CreateNewEntry(int key, void *value) {
    HashmapEntry *newEntry = (HashmapEntry *)calloc(1, sizeof(HashmapEntry));
    newEntry->key = key;
    newEntry->value = value;
    return newEntry;
}

// O(1) if no collision
// O(n) if collision
void Hashmap_Add(Hashmap *hashmap, int key, void *value) {
    int index = GetHashKey(hashmap, key);
    HashmapEntry *lastEntry = &hashmap->entries[index];

    // No Existing Entry
    // Create a new entry and add it to the hashmap
    if (!lastEntry->isOccupied) {
        hashmap->entries[index] = (HashmapEntry){key, value, true, NULL};
        AddToExistLinked(hashmap, lastEntry);
        return;
    }

    // Existing Entry
    // Traverse the linked list and add the new entry to the end
    HashmapEntry *newEntry = lastEntry->next;
    while (newEntry != NULL) {
        if (newEntry->key == key) {
            printf_s(stderr, "Key: %d already exists in hashmap", key);
            return;
        }
        lastEntry = newEntry;
        newEntry = newEntry->next;
    }
    lastEntry->next = CreateNewEntry(key, value);
    AddToExistLinked(hashmap, lastEntry->next);
}

// O(1) if no collision
// O(n) if collision
void *Hashmap_Get(Hashmap *hashmap, int key) {
    int index = GetHashKey(hashmap, key);
    HashmapEntry *entry = &hashmap->entries[index];

    // No Existing Entry
    // Return NULL
    if (!entry->isOccupied) {
        return NULL;
    }

    // Existing Entry
    // Traverse the linked list and return the value if found
    HashmapEntry *newEntry = entry->next;
    while (newEntry != NULL) {
        if (newEntry->key == key) {
            return newEntry->value;
        }
        newEntry = newEntry->next;
    }
    return NULL;
}

// O(1) if no collision
// O(n) if collision
void Hashmap_Remove(Hashmap *hashmap, int key) {
    int index = GetHashKey(hashmap, key);
    HashmapEntry *entry = &hashmap->entries[index];

    // No Existing Entry
    // Return NULL
    if (!entry->isOccupied) {
        return;
    }

    // Existing Entry
    // Traverse the linked list and remove the entry if found
    HashmapEntry *newEntry = entry->next;
    HashmapEntry *lastEntry = entry;
    while (newEntry != NULL) {
        if (newEntry->key == key) {
            lastEntry->next = newEntry->next;
            RemoveFromExistLinked(hashmap, newEntry);
            free(newEntry);
            return;
        }
        lastEntry = newEntry;
        newEntry = newEntry->next;
    }
}

void Hashmap_Clear(Hashmap *hashmap) {
    HashmapEntry *linked = hashmap->linked;
    if (linked == NULL) {
        return;
    }
    HashmapEntry *cur = linked->next;
    while(cur != NULL) {
        HashmapEntry *tmp = cur;
        cur = tmp->next;
        free(tmp);
    }
    hashmap->linked = NULL;
    hashmap->finalLinked = NULL;
}