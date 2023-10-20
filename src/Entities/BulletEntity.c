#include "BulletEntity.h"
#include <raymath.h>

void BulletEntity_Move(BulletEntity *bullet, float dt) {
    Vector2 dir = bullet->move_dir;
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, bullet->move_speed * dt);
    bullet->pos = Vector2Add(bullet->pos, dir);
}

void BulletEntity_Draw(BulletEntity *bullet) {
    DrawCircleV(bullet->pos, bullet->radius, bullet->color);
}