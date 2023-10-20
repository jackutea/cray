#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include "../Entities/MonsterEntity.h"
#include "../Entities/RoleEntity.h"
#include "../Entities/BulletEntity.h"
#include "../Entities/ChapterEntity.h"

typedef struct {

    RoleEntity *roleEntity;

    ChapterEntity *chapterEntity;
    
    MonsterEntity *monsters;
    int lastMonsterIndex;

    BulletEntity *bullets;
    int lastBulletIndex;

} Repository;

Repository *Repository_New(int maxMonsterSize, int maxBulletSize);
void Repository_TearDown(Repository *repository);
// ==== Bullet ====
RoleEntity *Repository_GetRoleEntity(Repository *repository);
void Repository_SetRoleEntity(Repository *repository, RoleEntity *roleEntity);
// ==== Monster ====
void Repository_AddMonsterEntity(Repository *repository, MonsterEntity *monsterEntity);
MonsterEntity *Repository_GetMonsterEntity(Repository *repository, int id);
void Repository_RemoveMonsterEntity(Repository *repository, int id);
// ==== Bullet ====
void Repository_AddBulletEntity(Repository *repository, BulletEntity *bulletEntity);
BulletEntity *Repository_GetBulletEntity(Repository *repository, int id);
void Repository_RemoveBulletEntity(Repository *repository, int id);

#endif // __REPOSITORY_H__