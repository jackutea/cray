#include "HitDomain.h"

void HitDomain_BulletHitMonster(MainContext *ctx, BulletEntity *bullet, MonsterEntity *monster) {
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
    bool isHit = CheckCollisionCircles(monster->pos, monster->radius, role->pos, role->radius);
    if (isHit) {

        // TODO: Play VFX

        // Calculate Damage
        int damage = monster->attr_atk;
        RoleEntity_BeHit(role, damage);

        Repository_RemoveMonsterEntity(ctx->repository, monster->id);
    }
}