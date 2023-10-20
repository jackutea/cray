#ifndef __VECTOR2INT_H__
#define __VECTOR2INT_H__

#include <raylib.h>

typedef struct Vector2Int {
    int x;
    int y;
} Vector2Int;

inline Vector2 Vector2Int_ToVector2(const Vector2Int *vector2Int) {
    return (Vector2) {
        .x = (float)vector2Int->x,
        .y = (float)vector2Int->y
    };
}

#endif