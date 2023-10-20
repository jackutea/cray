#ifndef __BULLET_ENTITY_H__
#define __BULLET_ENTITY_H__

#include <raylib.h>

typedef enum Enum_BulletFlyType {
    Enum_BulletFlyType_Linear = 1,
    Enum_BulletFlyType_TopDown = 2,
}Enum_BulletFlyType;

typedef struct {
    int id;
    int typeID;
    int attr_atk;
    Vector2 pos;
    Vector2 move_dir;
    float move_speed;
    float radius;
    Color color;
} BulletEntity;

void BulletEntity_Move(BulletEntity *bullet, float dt);
void BulletEntity_Draw(BulletEntity *bullet);

#endif // __BULLET_ENTITY_H__