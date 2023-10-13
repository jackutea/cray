#ifndef __HASHMAP_H_
#define __HASHMAP_H_

struct HashmapType;
typedef struct HashmapType Hashmap;

Hashmap *Hashmap_New(int size);
void Hashmap_TearDown(Hashmap *hashmap);
void Hashmap_Add(Hashmap *hashmap, int key, void *value);
void *Hashmap_Get(Hashmap *hashmap, int key);
void Hashmap_Remove(Hashmap *hashmap, int key);
void Hashmap_Clear(Hashmap *hashmap);

#endif