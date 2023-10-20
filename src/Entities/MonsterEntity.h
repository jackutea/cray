#ifndef __MONSTER_ENTITY_H__
#define __MONSTER_ENTITY_H__

#include <raylib.h>

typedef struct {
    int id;
    Vector2 position;
    Vector2 velocity;
    float radius;
    float speed;
    Color color;
} MonsterEntity;

#endif // __MONSTER_ENTITY_H__