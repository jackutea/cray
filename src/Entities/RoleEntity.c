#include <stdlib.h>
#include "RoleEntity.h"
#include "DrawUtils.h"

void RoleEntity_TearDown(RoleEntity *role) {
    free(role);
}

void RoleEntity_FromTM(RoleEntity *role, RoleEntity *tm) {
    role->typeID = tm->typeID;
    role->attr_hp = tm->attr_hp;
    role->attr_hpMax = tm->attr_hpMax;
    role->attr_bulletAtkAddition = 0;
    role->move_speed = tm->move_speed;
    role->bullet_typeID = tm->bullet_typeID;
    role->gun_cooldown = tm->gun_cooldown;
    role->gun_cooldownTimer = tm->gun_cooldownTimer;
    role->radius = tm->radius;
    role->color = tm->color;

    role->skill1_cd = tm->skill1_cd;
    role->skill1_cdTimer = 0;
    role->skill1_maintainSec = tm->skill1_maintainSec;
    role->skill1_maintainTimer = 0;

    role->skill2_cd = tm->skill2_cd;
    role->skill2_cdTimer = 0;
    role->skill2_maintainSec = tm->skill2_maintainSec;
    role->skill2_maintainTimer = 0;
    role->skill2_radius = tm->skill2_radius;
    role->skill2_isActive = false;

    role->skill3_cd = tm->skill3_cd;
    role->skill3_cdTimer = 0;
    role->skill3_maintainSec = tm->skill3_maintainSec;
    role->skill3_maintainTimer = 0;
    role->skill3_len = tm->skill3_len;
    role->skill3_width = tm->skill3_width;
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
    }
}

void RoleEntity_Cooldown(RoleEntity *role, float dt) {
    role->gun_cooldownTimer -= dt;
    if (role->gun_cooldownTimer < 0) {
        role->gun_cooldownTimer = 0;
    }

    // Skill 1
    role->skill1_cdTimer -= dt;
    if (role->skill1_cdTimer < 0) {
        role->skill1_cdTimer = 0;
    }

    role->skill1_maintainTimer -= dt;
    if (role->skill1_maintainTimer < 0) {
        role->skill1_maintainTimer = 0;
    }

    // Skill 2
    role->skill2_cdTimer -= dt;
    if (role->skill2_cdTimer < 0) {
        role->skill2_cdTimer = 0;
    }

    role->skill2_maintainTimer -= dt;
    if (role->skill2_maintainTimer < 0) {
        role->skill2_maintainTimer = 0;
    }

    role->skill3_cdTimer -= dt;
    if (role->skill3_cdTimer < 0) {
        role->skill3_cdTimer = 0;
    }

    role->skill3_maintainTimer -= dt;
    if (role->skill3_maintainTimer < 0) {
        role->skill3_maintainTimer = 0;
    }
}

Vector2 RoleEntity_GetMuzzlePos(RoleEntity *role) {
    float len = 2.0f * PPU;
    Vector2 dir = Vector2Scale(role->face, len);
    Vector2 muzzlePos = Vector2Add(role->pos, dir);
    return muzzlePos;
}

void RoleEntity_Draw(RoleEntity *role) {

    // Skill1
    if (role->skill1_maintainTimer > 0) {
        float radius = 100.0f * PPU;
        Color skill1Color = (Color){255, 255, 0, 60};
        float percent = role->skill1_maintainTimer / role->skill1_maintainSec;
        DrawCircleSector(role->pos, radius, 0, 360 * percent, 0, skill1Color);
        DrawText("Time Freeze!", role->pos.x + 160, role->pos.y, 14, BLACK);
    }

    // SKill2
    if (role->skill2_maintainTimer > 0) {
        float radius = role->skill2_radius;
        Color skill2Color = (Color){255, 255, 0, 60};
        float percent = (role->skill2_maintainSec - role->skill2_maintainTimer) / role->skill2_maintainSec;
        DrawRing(role->skill2_center, 0, radius * percent, 0, 360, 0, skill2Color);
        DrawCircleLines(role->skill2_center.x, role->skill2_center.y, radius, skill2Color);
        DrawText("Nuclear Bomb!", role->skill2_center.x, role->skill2_center.y, 14, BLACK);
    }

    // Skill3
    if (role->skill3_maintainTimer > 0) {
        float len = role->skill3_len;
        Color rayColor = (Color){0, 162, 230, 60};
        Vector2 dir = Vector2Scale(role->face, len);
        Vector2 endPos = Vector2Add(role->pos, dir);
        DrawLineEx(role->pos, endPos, role->skill3_width, rayColor);
        DrawText("Lightning-Ray!", role->pos.x + 160, role->pos.y, 14, BLACK);
    }

    // Draw Body
    float innerRadius = role->radius * 0.8f;
    DrawCircleV(role->pos, innerRadius, role->color);

    // Draw Hp
    DrawUtils_PercentRing(role->pos, role->radius, role->attr_hp, role->attr_hpMax, COLOR_HP);

    // Draw Face line
    float len = 2.0f * PPU;
    Vector2 dir = Vector2Scale(role->face, len);
    Vector2 endPos = Vector2Add(role->pos, dir);
    DrawLineEx(role->pos, endPos, 4, role->color);

}