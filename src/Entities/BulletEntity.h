#ifndef __BULLET_ENTITY_H__
#define __BULLET_ENTITY_H__

#include <raylib.h>

typedef struct {
    int id;
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} BulletEntity;

#endif // __BULLET_ENTITY_H__