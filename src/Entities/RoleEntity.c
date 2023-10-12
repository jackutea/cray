#include <stdlib.h>
#include "RoleEntity.h"

RoleEntity* RoleEntity_New() {
    RoleEntity* role = (RoleEntity*)calloc(1, sizeof(RoleEntity));
    role->pos = (Vector2){0, 0};
    role->move_speed = 96;
    return role;
}

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float delta_time) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * delta_time);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_Draw(RoleEntity *role) {
    DrawCircleV(role->pos, 10, RED);
}