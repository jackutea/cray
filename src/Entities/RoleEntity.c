#include <stdlib.h>
#include "RoleEntity.h"

RoleEntity* RoleEntity_Create() {
    RoleEntity* role = (RoleEntity*)calloc(1, sizeof(RoleEntity));
    role->pos = (Vector2){0, 0};
    role->move_speed = 5;
    return role;
}

void RoleEntity_Move(RoleEntity *role, Vector2 dir) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}