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