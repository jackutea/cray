#include <stdlib.h>
#include "RoleEntity.h"

RoleEntity* RoleEntity_Create() {
    RoleEntity* role = (RoleEntity*)calloc(1, sizeof(RoleEntity));
    role->pos = (Vector2){0, 0};
    role->move_speed = 960;
    return role;
}

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float delta_time) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * delta_time);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}