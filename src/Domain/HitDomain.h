#ifndef __HITDOMAIN_H__
#define __HITDOMAIN_H__

#include "../Context/MainContext.h"

void HitDomain_BulletHitMonster(MainContext *ctx, const BulletEntity *bullet, const MonsterEntity *monster);
void HitDomain_MonsterHitRole(MainContext *ctx, MonsterEntity *monster, RoleEntity *role);

#endif // __HITDOMAIN_H__