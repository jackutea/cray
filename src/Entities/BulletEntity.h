#ifndef __BULLET_ENTITY_H__
#define __BULLET_ENTITY_H__

#include <raylib.h>

typedef struct {
    int id;
    int typeID;
    Vector2 pos;
    Vector2 move_dir;
    float move_speed;
    float radius;
    Color color;
} BulletEntity;

void BulletEntity_Move(BulletEntity *bullet, float dt);
void BulletEntity_Draw(BulletEntity *bullet);

#endif // __BULLET_ENTITY_H__