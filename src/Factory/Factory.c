#include "Factory.h"
#include "../GameDefines.h"
#include <stdlib.h>

static int role_id_record = 0;
static int monster_id_record = 0;
static int bullet_id_record = 0;

ChapterEntity *Factory_SpawnChapter(MainContext *mainContext, int chapter) {

    Templates *templates = mainContext->templates;
    bool has;
    ChapterEntity tm = Templates_GetChapterEntity(templates, chapter, &has);
    if (!has) {
        TraceLog(LOG_ERROR, "Factory_SpawnChapter: chapter %d not found in templates\n", chapter);
        return NULL;
    }

    ChapterEntity *chapterEntity = (ChapterEntity *)calloc(1, sizeof(ChapterEntity));
    ChapterEntity_FromTM(chapterEntity, &tm);
    chapterEntity->aliveRadius = 80.0f * PPU;
    chapterEntity->alive_scale_speed = 0.5f * PPU;

    // Repository
    Repository_SetChapterEntity(mainContext->repository, chapterEntity);

    return chapterEntity;
}

RoleEntity *Factory_SpawnRole(MainContext *mainContext, int typeID, Vector2 pos) {

    Templates *templates = mainContext->templates;
    bool has;
    RoleEntity tm = Templates_GetRoleEntity(templates, typeID, &has);
    if (!has) {
        TraceLog(LOG_ERROR, "Factory_SpawnRole: typeID %d not found in templates\n", typeID);
        return NULL;
    }

    RoleEntity *role = (RoleEntity *)calloc(1, sizeof(RoleEntity));
    RoleEntity_FromTM(role, &tm);
    role->id = role_id_record++;
    role->pos = pos;
    role->face = (Vector2){0, -1};

    // Repository
    Repository_SetRoleEntity(mainContext->repository, role);

    return role;
}

void Factory_SpawnMonster(MainContext *mainContext, int typeID, Vector2 pos) {

    Templates *templates = mainContext->templates;
    bool has;
    MonsterEntity tm = Templates_GetMonsterEntity(templates, typeID, &has);
    if (!has) {
        TraceLog(LOG_ERROR, "Factory_SpawnMonster: typeID %d not found in templates\n", typeID);
        return;
    }

    MonsterEntity monster;
    MonsterEntity_FromTM(&monster, &tm);
    monster.id = monster_id_record++;
    monster.pos = pos;
    monster.move_dir = (Vector2){0, -1};

    // Repository
    Repository_AddMonsterEntity(mainContext->repository, monster);

}

void Factory_SpawnBullet(MainContext *mainContext, int typeID, Vector2 pos, Vector2 move_dir) {

    Templates *templates = mainContext->templates;
    bool has;
    BulletEntity tm = Templates_GetBulletEntity(templates, typeID, &has);
    if (!has) {
        TraceLog(LOG_ERROR, "Factory_SpawnBullet: typeID %d not found in templates\n", typeID);
        return;
    }

    BulletEntity bullet;
    BulletEntity_FromTM(&bullet, &tm);
    bullet.id = bullet_id_record++;
    bullet.pos = pos;
    bullet.move_dir = move_dir;

    // Repository
    Repository_AddBulletEntity(mainContext->repository, bullet);
}