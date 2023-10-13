#ifndef __ROLEENTITY_H
#define __ROLEENTITY_H

#include <raylib.h>
#include <raymath.h>

struct RoleEntityType;
typedef struct RoleEntityType RoleEntity;

RoleEntity *RoleEntity_New();
void RoleEntity_TearDown(RoleEntity *role);
void RoleEntity_Init(RoleEntity *role, int id, float move_speed);
void RoleEntity_Move(RoleEntity *role, Vector2 dir, float delta_time);
void RoleEntity_Draw(RoleEntity *role);
const Vector2 *RoleEntity_GetPos(RoleEntity *role);

#endif // __ROLEENTITY_H