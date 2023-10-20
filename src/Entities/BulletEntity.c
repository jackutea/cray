#include "BulletEntity.h"
#include <raymath.h>

void BulletEntity_FromTM(BulletEntity *entity, BulletEntity *tm) {
    entity->typeID = tm->typeID;
    entity->attr_atk = tm->attr_atk;
    entity->move_speed = tm->move_speed;
    entity->radius = tm->radius;
    entity->color = tm->color;
}

void BulletEntity_Move(BulletEntity *bullet, float dt) {
    Vector2 dir = bullet->move_dir;
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, bullet->move_speed * dt);
    bullet->pos = Vector2Add(bullet->pos, dir);
}

void BulletEntity_Draw(BulletEntity *bullet) {
    DrawCircleV(bullet->pos, bullet->radius, bullet->color);
}