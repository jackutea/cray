#include <stdlib.h>
#include "RoleEntity.h"

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float dt) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * dt);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_Face(RoleEntity *role, Vector2 targetPos) {
    Vector2 dir = Vector2Subtract(targetPos, role->pos);
    dir = Vector2Normalize(dir);
    if (dir.x != 0 && dir.y != 0) {
        role->face = dir;
    } else {
        role->face = (Vector2){0, -1};
    }
}

void RoleEntity_Draw(RoleEntity *role) {

    DrawCircleV(role->pos, role->radius, role->color);

    // Draw Face line
    float len = 2.0f * PPU;
    Vector2 dir = Vector2Scale(role->face, len);
    Vector2 endPos = Vector2Add(role->pos, dir);
    DrawLine((int)role->pos.x, (int)role->pos.y, (int)endPos.x, (int)endPos.y, role->color);
}