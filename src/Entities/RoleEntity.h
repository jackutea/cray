#ifndef __ROLEENTITY_H
#define __ROLEENTITY_H

#include <raylib.h>
#include <raymath.h>
#include "GunComponent.h"
#include "../GameDefines.h"

struct RoleEntityType {
    int id;
    int typeID;
    Vector2 pos;
    Vector2 face;
    float move_speed;
    GunComponent gunCom;
    float radius;
    Color color;
};
typedef struct RoleEntityType RoleEntity;

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float dt);
void RoleEntity_Face(RoleEntity *role, Vector2 targetPos);
void RoleEntity_Draw(RoleEntity *role);

#endif // __ROLEENTITY_H