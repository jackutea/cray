#include "HitDomain.h"

void HitDomain_BulletHitMonster(MainContext *ctx, const BulletEntity *bullet, const MonsterEntity *monster) {
    bool isHit = CheckCollisionCircles(bullet->pos, bullet->radius, monster->pos, monster->radius);
    if (isHit) {

        // TODO: Play VFX

        // Calculate Damage
        int damage = bullet->attr_atk;
        MonsterEntity_BeHit(monster, damage);
        if (monster->attr_hp <= 0) {
            Repository_RemoveMonsterEntity(ctx->repository, monster->id);
        }

        Repository_RemoveBulletEntity(ctx->repository, bullet->id);
    }
}

void HitDomain_MonsterHitRole(MainContext *ctx, MonsterEntity *monster, RoleEntity *role) {
}