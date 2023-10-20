#include "Templates.h"
#include <stdlib.h>

Templates *Templates_New() {
    Templates *templates = calloc(1, sizeof(Templates));
    return templates;
}

void Templates_Init(Templates *templates) {

    // Chapters
    ChapterEntity *chapters = calloc(3, sizeof(ChapterEntity));
    templates->chapters = chapters;

    // Roles
    RoleEntity *roles = calloc(1, sizeof(RoleEntity));
    templates->roles = roles;

    // Monsters
    MonsterEntity *monsters = calloc(10, sizeof(MonsterEntity));
    templates->monsters = monsters;

    // Bullets
    BulletEntity *bullets = calloc(10, sizeof(BulletEntity));
    templates->bullets = bullets;
}

ChapterEntity Templates_GetChapterEntity(Templates *templates, int chapter, bool *has) {
    ChapterEntity *chapters = templates->chapters;
    for (int i = 0; i < 3; i++) {
        if (chapters[i].chapter == chapter) {
            *has = true;
            return chapters[i];
        }
    }
    *has = false;
    return (ChapterEntity){0};
}

RoleEntity Templates_GetRoleEntity(Templates *templates, int typeID, bool *has) {
    RoleEntity *roles = templates->roles;
    for (int i = 0; i < 1; i++) {
        if (roles[i].typeID == typeID) {
            *has = true;
            return roles[i];
        }
    }
    *has = false;
    return (RoleEntity){0};
}

MonsterEntity Templates_GetMonsterEntity(Templates *templates, int typeID, bool *has) {
    MonsterEntity *monsters = templates->monsters;
    for (int i = 0; i < 10; i++) {
        if (monsters[i].typeID == typeID) {
            *has = true;
            return monsters[i];
        }
    }
    *has = false;
    return (MonsterEntity){0};
}

BulletEntity Templates_GetBulletEntity(Templates *templates, int typeID, bool *has) {
    BulletEntity *bullets = templates->bullets;
    for (int i = 0; i < 10; i++) {
        if (bullets[i].typeID == typeID) {
            *has = true;
            return bullets[i];
        }
    }
    *has = false;
    return (BulletEntity){0};
}