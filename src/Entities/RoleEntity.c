#include <stdlib.h>
#include "RoleEntity.h"

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float dt) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * dt);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_Draw(RoleEntity *role) {
    DrawCircleV(role->pos, role->radius, RED);
}