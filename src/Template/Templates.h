#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__

#include "../Entities/MonsterEntity.h"
#include "../Entities/RoleEntity.h"
#include "../Entities/BulletEntity.h"
#include "../Entities/ChapterEntity.h"

typedef struct {
    ChapterEntity *chapters;
    RoleEntity *roles;
    MonsterEntity *monsters;
    BulletEntity *bullets;
} Templates;

Templates *Templates_New();
void Templates_Init(Templates *templates);
ChapterEntity Templates_GetChapterEntity(Templates *templates, int chapter, bool *has);
RoleEntity Templates_GetRoleEntity(Templates *templates, int typeID, bool *has);
MonsterEntity Templates_GetMonsterEntity(Templates *templates, int typeID, bool *has);
BulletEntity Templates_GetBulletEntity(Templates *templates, int typeID, bool *has);

#endif // __TEMPLATE_H__