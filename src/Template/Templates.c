#include "Templates.h"
#include <stdlib.h>

Templates *Templates_New() {
    Templates *templates = calloc(1, sizeof(Templates));
    return templates;
}

// ==== Private ====
ChapterEntity Chapter_New(int chapter, int monster_level_min, int monster_level_max, int monster_count_rd,
                          int wave_count, int boss_typeID) {

    ChapterEntity entity;
    entity.chapter = chapter;
    entity.wave_current = 0;
    entity.wave_count = wave_count;

    // Normal Monster
    int *monster_level = calloc(wave_count, sizeof(int));
    int *monster_count = calloc(wave_count, sizeof(int));
    for (int i = 0; i < wave_count; i++) {
        monster_level[i] = GetRandomValue(monster_level_min, monster_level_max);
        monster_count[i] = GetRandomValue(monster_count_rd / 2, monster_count_rd);
    }

    // Boss
    entity.boss_typeID = boss_typeID;

    entity.wave_monster_level = monster_level;
    entity.wave_monster_count = monster_count;

    return entity;
}

RoleEntity Role_New(int typeID, int hp, int speed, float radius, int bullet_typeID, Color color) {
    RoleEntity entity;
    entity.typeID = typeID;
    entity.attr_hp = hp;
    entity.attr_hpMax = hp;
    entity.move_speed = speed * PPU;
    entity.radius = radius * PPU;
    entity.bullet_typeID = bullet_typeID;
    entity.gun_cooldownTimer = 0.0f;
    entity.gun_cooldown = 0.5f;
    entity.color = color;

    entity.skill1_cd = 20.0f;
    entity.skill1_maintainSec = 5.0f;
    entity.skill2_cd = 30.0f;
    entity.skill2_maintainSec = 3.0f;
    entity.skill2_radius = 500.0f;

    entity.skill3_cd = 40.0f;
    entity.skill3_maintainSec = 5.0f;
    entity.skill3_len = 99999.0f;
    entity.skill3_width = 40.0f;
    return entity;
}

MonsterEntity Monster_New(int typeID, bool isBoss, int level, int hp, int atk, float speed, float radius, Color color) {
    MonsterEntity entity;
    entity.typeID = typeID;
    entity.isBoss = isBoss;
    entity.level = level;
    entity.attr_hp = hp;
    entity.attr_hpMax = hp;
    entity.attr_atk = atk;
    entity.move_speed = speed * PPU;
    entity.radius = radius * PPU;
    entity.color = color;
    return entity;
}

BulletEntity Bullet_New(int typeID, int atk, float speed, float radius, Color color) {
    BulletEntity entity;
    entity.typeID = typeID;
    entity.attr_atk = atk;
    entity.move_speed = speed * PPU;
    entity.radius = radius * PPU;
    entity.color = color;
    return entity;
}

void Templates_Init(Templates *templates) {

    // Chapters
    ChapterEntity *chapters = (ChapterEntity *)calloc(4, sizeof(ChapterEntity));
    chapters[0] = Chapter_New(1, 1, 1, 5, 3, 1001);
    chapters[1] = Chapter_New(2, 1, 2, 8, 4, 1002);
    chapters[2] = Chapter_New(3, 2, 3, 12, 4, 1003);
    chapters[3] = Chapter_New(4, 3, 4, 15, 5, 1004);
    templates->chapters = chapters;

    // Roles
    RoleEntity *roles = calloc(1, sizeof(RoleEntity));
    roles[0] = Role_New(1, 10, 5, 1, 1, GREEN);
    templates->roles = roles;

    // Monsters
    int monster_count = 7;
    int boss_count = 4;
    MonsterEntity *monsters = (MonsterEntity *)calloc(monster_count + boss_count, sizeof(MonsterEntity));
    monsters[0] = Monster_New(1, false, 1, 2, 1, 6, 1, RED);
    monsters[1] = Monster_New(2, false, 2, 5, 2, 6, 2, RED);
    monsters[2] = Monster_New(3, false, 3, 10, 4, 7, 4, RED);
    monsters[3] = Monster_New(4, false, 4, 20, 5, 6, 5, RED);
    monsters[4] = Monster_New(5, false, 5, 10, 6, 6.5f, 6, RED);
    monsters[5] = Monster_New(6, false, 6, 12, 8, 7.5f, 8, RED);
    monsters[6] = Monster_New(7, false, 7, 14, 9, 7.5f, 9, RED);
    templates->monsters = monsters;

    // Bosses
    monsters[monster_count + 0] = Monster_New(1001, true, 3, 30, 3, 4.5f, 5, GOLD);
    monsters[monster_count + 1] = Monster_New(1002, true, 7, 200, 7, 5.5f, 7, GOLD);
    monsters[monster_count + 2] = Monster_New(1003, true, 10, 500, 10, 6.5f, 10, GOLD);
    monsters[monster_count + 3] = Monster_New(1004, true, 10, 1500, 10, 6.5f, 12, GOLD);

    // Bullets
    BulletEntity *bullets = calloc(10, sizeof(BulletEntity));
    bullets[0] = Bullet_New(1, 1, 15, 0.25f, GRAY);
    bullets[1] = Bullet_New(2, 2, 15, 0.3f, GRAY);
    bullets[2] = Bullet_New(3, 3, 15, 0.35f, GRAY);
    bullets[3] = Bullet_New(4, 4, 16, 0.4f, GRAY);
    bullets[4] = Bullet_New(5, 5, 16, 0.45f, GRAY);
    bullets[5] = Bullet_New(6, 6, 16, 0.5f, GRAY);
    bullets[6] = Bullet_New(7, 7, 17, 0.55f, GRAY);
    bullets[7] = Bullet_New(8, 8, 17, 1.0f, GRAY);
    bullets[8] = Bullet_New(9, 9, 17, 1.1f, GRAY);
    bullets[9] = Bullet_New(10, 20, 7, 3.0f, GRAY);
    templates->bullets = bullets;
}

// ==== Public API ====
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

MonsterEntity Templates_GetMonsterEntityByLevel(Templates *templates, int level, bool *has) {
    MonsterEntity *monsters = templates->monsters;
    for (int i = 0; i < 10; i++) {
        if (monsters[i].level == level && !monsters[i].isBoss) {
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