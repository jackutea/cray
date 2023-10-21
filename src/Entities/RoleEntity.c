#include "RoleEntity.h"
#include "DrawUtils.h"

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}

void RoleEntity_FromTM(RoleEntity *role, RoleEntity *tm) {
    role->typeID = tm->typeID;
    role->attr_hp = tm->attr_hp;
    role->attr_hpMax = tm->attr_hpMax;
    role->move_speed = tm->move_speed;
    role->bullet_typeID = tm->bullet_typeID;
    role->gun_cooldown = tm->gun_cooldown;
    role->gun_cooldownTimer = tm->gun_cooldownTimer;
    role->radius = tm->radius;
    role->color = tm->color;
}

void RoleEntity_Move(RoleEntity *role, Vector2 dir, float dt) {
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, role->move_speed * dt);
    role->pos = Vector2Add(role->pos, dir);
}

void RoleEntity_BeHit(RoleEntity *role, int damage) {
    role->attr_hp -= damage;
    if (role->attr_hp < 0) {
        role->attr_hp = 0;
    }
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

void RoleEntity_Cooldown(RoleEntity *role, float dt) {
    role->gun_cooldownTimer -= dt;
    if (role->gun_cooldownTimer < 0) {
        role->gun_cooldownTimer = 0;
    }
}

Vector2 RoleEntity_GetMuzzlePos(RoleEntity *role) {
    float len = 2.0f * PPU;
    Vector2 dir = Vector2Scale(role->face, len);
    Vector2 muzzlePos = Vector2Add(role->pos, dir);
    return muzzlePos;
}

void RoleEntity_Draw(RoleEntity *role) {

    // Draw Body
    float innerRadius = role->radius * 0.8f;
    DrawCircleV(role->pos, innerRadius, role->color);

    // Draw Hp
    DrawUtils_HpRing(role->pos, role->radius, role->attr_hp, role->attr_hpMax, COLOR_HP);

    // Draw Face line
    float len = 2.0f * PPU;
    Vector2 dir = Vector2Scale(role->face, len);
    Vector2 endPos = Vector2Add(role->pos, dir);
    DrawLineEx(role->pos, endPos, 4, role->color);
}