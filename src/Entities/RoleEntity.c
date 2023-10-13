#include <stdlib.h>
#include "RoleEntity.h"

struct RoleEntityType {
    // ==== Logic ====
    Vector2 pos;
    int id;
    float move_speed;

    // ==== Renderer ====
    // TODO: Model
};

RoleEntity *RoleEntity_New() {
    RoleEntity *role = (RoleEntity *)calloc(1, sizeof(RoleEntity));
    return role;
}

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}

void RoleEntity_Init(RoleEntity *role, int id, float move_speed) {
    role->id = id;
    role->move_speed = move_speed;
}

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float delta_time) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * delta_time);
    role->pos = Vector2Add(role->pos, dir);
}

const Vector2 *RoleEntity_GetPos(RoleEntity *role) {
    return &role->pos;
}

void RoleEntity_Draw(RoleEntity *role) {
    DrawCircleV(role->pos, 10, RED);
}