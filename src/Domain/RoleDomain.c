#include "RoleDomain.h"
#include "../Factory/Factory.h"

void RoleDomain_Shoot(MainContext *ctx, RoleEntity *role, bool isShootDown, float dt) {

    if (!isShootDown) {
        return;
    }

    if (role->gun_cooldownTimer > 0) {
        return;
    }

    role->gun_cooldownTimer = role->gun_cooldown;

    Vector2 muzzle = RoleEntity_GetMuzzlePos(role);
    Factory_SpawnBullet(ctx, role->bullet_typeID, muzzle, role->face, role->attr_bulletAtkAddition);
}

void RoleDomain_SkillCast(MainContext *ctx, RoleEntity *role, int skillIndexDown, float dt) {
    if (skillIndexDown <= 0) {
        return;
    }

    // Skill1: Time Lock
    if (skillIndexDown == 1) {
        if (role->skill1_cdTimer <= 0) {
            role->skill1_cdTimer = role->skill1_cd;
            role->skill1_maintainTimer = role->skill1_maintainSec;
        }
    }

    // Skill2: Nuclear Bomb Falls
    if (skillIndexDown == 2) {
        if (role->skill2_cdTimer <= 0) {
            role->skill2_cdTimer = role->skill2_cd;
            role->skill2_maintainTimer = role->skill2_maintainSec;
            role->skill2_isActive = true;
            role->skill2_center = role->pos;
        }
    }

    // Skill3: Lightning-Ray
    if (skillIndexDown == 3) {
        if (role->skill3_cdTimer <= 0) {
            role->skill3_cdTimer = role->skill3_cd;
            role->skill3_maintainTimer = role->skill3_maintainSec;
        }
    }
}