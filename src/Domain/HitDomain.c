#include "HitDomain.h"
#include "../Factory/Factory.h"

void HitDomain_BulletHitMonster(MainContext *ctx, BulletEntity *bullet, MonsterEntity *monster) {
    bool isHit = CheckCollisionCircles(bullet->pos, bullet->radius, monster->pos, monster->radius);
    if (isHit) {

        // TODO: Play VFX

        // Calculate Damage
        int damage = bullet->attr_atk;
        MonsterEntity_BeHit(monster, damage);
        if (monster->attr_hp <= 0) {
            Factory_TearDownMonster(ctx, monster);
        }

        Factory_TearDownBullet(ctx, bullet);
    }
}

void HitDomain_MonsterHitRole(MainContext *ctx, MonsterEntity *monster, RoleEntity *role) {
    bool isHit = CheckCollisionCircles(monster->pos, monster->radius, role->pos, role->radius);
    if (isHit) {

        // TODO: Play VFX

        // Calculate Damage
        int damage = monster->attr_atk;
        RoleEntity_BeHit(role, damage);

        Factory_TearDownMonster(ctx, monster);
    }
}