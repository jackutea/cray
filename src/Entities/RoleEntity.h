#ifndef __ROLEENTITY_H
#define __ROLEENTITY_H

#include <raylib.h>
#include <raymath.h>
#include "../GameDefines.h"

typedef struct {
    int id;
    int typeID;
    int attr_hp;
    int attr_hpMax;
    float move_speed;
    int bullet_typeID;
    float gun_cooldown;
    float gun_cooldownTimer;
    float radius;
    Color color;
    Vector2 pos;
    Vector2 face;
} RoleEntity;

void RoleEntity_FromTM(RoleEntity *role, RoleEntity *tm);
void RoleEntity_Move(RoleEntity *role, Vector2 dir, float dt);
void RoleEntity_Cooldown(RoleEntity *role, float dt);
void RoleEntity_BeHit(RoleEntity *role, int damage);
void RoleEntity_Face(RoleEntity *role, Vector2 targetPos);
Vector2 RoleEntity_GetMuzzlePos(RoleEntity *role);
void RoleEntity_Draw(RoleEntity *role);

#endif // __ROLEENTITY_H