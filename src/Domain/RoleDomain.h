#ifndef __ROLE_DOMAIN_H__
#define __ROLE_DOMAIN_H__

#include "../Context/MainContext.h"

void RoleDomain_Shoot(MainContext *ctx, RoleEntity *role, bool isShootDown, float dt);
void RoleDomain_SkillCast(MainContext *ctx, RoleEntity *role, int skillIndexDown, float dt);

#endif // __ROLE_DOMAIN_H__