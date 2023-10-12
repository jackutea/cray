#ifndef __ROLEENTITY_H
#define __ROLEENTITY_H

#include <raylib.h>
#include <raymath.h>

typedef struct {
    // ==== Logic ====
    Vector2 pos;
    float move_speed;

    // ==== Renderer ====
    // TODO: Model
} RoleEntity;

RoleEntity* RoleEntity_New();
void RoleEntity_TearDown(RoleEntity *role);
void RoleEntity_Move(RoleEntity *role, Vector2 dir, float delta_time);
void RoleEntity_Draw(RoleEntity *role);

#endif // __ROLEENTITY_H