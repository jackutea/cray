#include "GameController.h"
#include "../Domain/RoleDomain.h"
#include "../Domain/HitDomain.h"
#include "../Factory/Factory.h"
#include "../RaylibExtension.h"

Vector2 GetSpawnPosByDir(MainContext *ctx, Enum_FromDir dir) {
    Vector2Int pos;
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    Vector2Int half =
        (Vector2Int){.x = (int)role->pos.x + ctx->windowSize.x / 2, .y = (int)role->pos.y + ctx->windowSize.y / 2};
    if (dir == Enum_FromDir_Left) {
        pos.x = -half.x;
        pos.y = GetRandomValue(-half.y, half.y);
    } else if (dir == Enum_FromDir_Right) {
        pos.x = half.x;
        pos.y = GetRandomValue(-half.y, half.y);
    } else if (dir == Enum_FromDir_Top) {
        pos.x = GetRandomValue(-half.x, half.x);
        pos.y = -half.y;
    } else if (dir == Enum_FromDir_Bottom) {
        pos.x = GetRandomValue(-half.x, half.x);
        pos.y = half.y;
    }
    return Vector2Int_ToVector2(&pos);
}

Vector2 GetRandomSpawnPosDir(MainContext *ctx) {
    Enum_FromDir dir = (Enum_FromDir)GetRandomValue(0, 3);
    return GetSpawnPosByDir(ctx, dir);
}

void GameController_Enter(MainContext *ctx) {
    // Chapter: Spawn
    ChapterEntity *chapter = Factory_SpawnChapter(ctx, 1);
    // Role: Spawn
    RoleEntity *role = Factory_SpawnRole(ctx, 1, (Vector2){0});
}

void GameController_Update(MainContext *ctx, float dt) {

    // Role: Rotate
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    RoleEntity_Face(role, ctx->inputCore->mouseWorldPos);

    // Bullet: Spawn
}

void GameController_FixedUpdate(MainContext *ctx, float fixdt) {

    // Chapter: Spawn Monster
    ChapterEntity *chapter = Repository_GetChapterEntity(ctx->repository);
    bool isFinalWave = ChapterEntity_IsFinalWave(chapter);
    if (!isFinalWave) {
        if (chapter->wave_timer <= 0) {
            chapter->wave_timer = 5.0f;
            ChapterEntity_NextWave(chapter);
            bool isBossWave = chapter->wave_current == chapter->wave_count - 1;
            if (!isBossWave) {
                int curMonsterLevel = chapter->wave_monster_level[chapter->wave_current];
                int curMonsterCount = chapter->wave_monster_count[chapter->wave_current];
                for (int i = 0; i < curMonsterCount; i += 1) {
                    Factory_SpawnMonsterByLevel(ctx, curMonsterLevel, GetRandomSpawnPosDir(ctx));
                }
            } else {
                Factory_SpawnMonster(ctx, chapter->boss_typeID, GetRandomSpawnPosDir(ctx));
            }

        } else {
            chapter->wave_timer -= fixdt;
        }
    }

    // Chapter: Scale Alive Radius
    ChapterEntity_ScaleAliveRadius(chapter, fixdt);

    // ==== Role ====
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);

    // Role: Cooldown
    RoleEntity_Cooldown(role, fixdt);

    // Role: Move
    RoleEntity_Move(role, ctx->inputCore->moveAxis, fixdt);

    // Role: Shoot
    RoleDomain_Shoot(ctx, role, ctx->inputCore->isMouseLeftDown, fixdt);

    // Role: Cast
    RoleDomain_SkillCast(ctx, role, ctx->inputCore->skillIndexDown, fixdt);

    bool isLockMonster = role->skill1_maintainTimer > 0;

    // Bullet: Move
    BulletEntity *bullets = ctx->repository->bullets;
    int lastBulletIndex = ctx->repository->lastBulletIndex;
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        BulletEntity_Move(bullet, fixdt);
    }

    // Monster: Move
    float monsterSpeedScale = isLockMonster ? 0.2f : 1.0f;
    MonsterEntity *monsters = ctx->repository->monsters;
    int lastMonsterIndex = ctx->repository->lastMonsterIndex;
    for (int i = 0; i < lastMonsterIndex; i++) {
        MonsterEntity *monster = &monsters[i];
        MonsterEntity_FaceTo(monster, role->pos);
        MonsterEntity_Move(monster, fixdt * monsterSpeedScale);
    }

    // Hit: Bullet -> Monster
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        for (int j = 0; j < lastMonsterIndex; j++) {
            MonsterEntity *monster = &monsters[j];
            HitDomain_BulletHitMonster(ctx, bullet, monster);
        }
    }

    // Hit: Monster -> Role
    for (int i = 0; i < lastMonsterIndex; i++) {
        MonsterEntity *monster = &monsters[i];
        HitDomain_MonsterHitRole(ctx, monster, role);
    }

    // Hit: Role Skill2 Bomb -> Monster
    if (role->skill2_isActive && role->skill2_maintainTimer <= 0) {
        role->skill2_isActive = false;
        for (int i = 0; i < lastMonsterIndex; i++) {
            MonsterEntity *monster = &monsters[i];
            if (CheckCollisionCircles(role->skill2_center, role->skill2_radius, monster->pos, monster->radius)) {
                monster->attr_hp -= 10;
                if (monster->attr_hp <= 0) {
                    Factory_TearDownMonster(ctx, monster);
                }
            }
        }
        ctx->mainCameraCore->shakeMaintain = 1.0f;
    }

    // Hit: Role Skill3 Ray -> Monster
    if (role->skill3_maintainTimer > 0) {
        if (role->skill3_interval <= 0) {
            role->skill3_interval = 0.1f;
            for (int i = 0; i < lastMonsterIndex; i++) {
                // 调用 CheckCollisionCircleOBB
                MonsterEntity *monster = &monsters[i];
                Vector2 boxCenter = Vector2Add(role->pos, (Vector2){0, role->skill3_len / 2});
                Vector2 boxSize = (Vector2){role->skill3_width, role->skill3_len};
                float boxAngle = Vector2Angle(role->face, (Vector2){0, 1});
                bool isHit = CheckCollisionCircleOBB(monster->pos, monster->radius, boxCenter, boxSize, boxAngle);
                if (isHit) {
                    monster->attr_hp -= 10;
                    if (monster->attr_hp <= 0) {
                        Factory_TearDownMonster(ctx, monster);
                    }
                }
            }
        ctx->mainCameraCore->shakeMaintain = 0.1f;
        ctx->mainCameraCore->shakeLevel = 1;
        } else {
            role->skill3_interval -= fixdt;
        }
    }

    // Bullet: Move Out Of AliveRadius
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        bool isBulletInside = CheckCollisionPointCircle(bullet->pos, Vector2Zero(), chapter->aliveRadius);
        if (!isBulletInside) {
            Factory_TearDownBullet(ctx, bullet);
        }
    }

    // Role: Move Out Of AliveRadius
    bool isRoleInside = CheckCollisionCircles(role->pos, role->radius, Vector2Zero(), chapter->aliveRadius);
    if (!isRoleInside) {
        ctx->gameStateEntity->OnGameLoseHandle();
    }
}

void GameController_LateUpdate(MainContext *ctx, float dt) {

    // Role Dead
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    if (role->attr_hp <= 0) {
        ctx->gameStateEntity->OnGameLoseHandle();
        return;
    }

    // Chapter Clear
    ChapterEntity *chapter = Repository_GetChapterEntity(ctx->repository);
    bool isFinal = ChapterEntity_IsFinalWave(chapter);
    if (isFinal && ctx->repository->lastMonsterIndex <= 0) {
        ChapterEntity *newChapter = Factory_SpawnChapter(ctx, chapter->chapter + 1);
        if (newChapter == NULL) {
            // 通关
            ctx->gameStateEntity->OnGameWinHandle();
        } else {
            // 切下一关
            // Role: Clear
            RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
            role->pos = (Vector2){0};

            // 升级
            ctx->gameStateEntity->OnGameUpgradeHandle(
                Enum_UpgradeOptionType_BulletAtk, Enum_UpgradeOptionType_GunCooldown, Enum_UpgradeOptionType_MoveSpeed);
        }
    }
}

void GameController_DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt) {

    const Color bg = DARKGREEN;
    ClearBackground(bg);

    // Draw Chapter
    ChapterEntity *chapter = Repository_GetChapterEntity(ctx->repository);
    ChapterEntity_Draw(chapter);

    // Draw Role
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    RoleEntity_Draw(role);

    // Draw Monsters
    MonsterEntity *monsters = ctx->repository->monsters;
    int lastMonsterIndex = ctx->repository->lastMonsterIndex;
    for (int i = 0; i < lastMonsterIndex; i++) {
        MonsterEntity *monster = &monsters[i];
        MonsterEntity_Draw(monster);
    }

    // Draw Bullets
    BulletEntity *bullets = ctx->repository->bullets;
    int lastBulletIndex = ctx->repository->lastBulletIndex;
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        BulletEntity_Draw(bullet);
    }

    CameraCore_Follow(mainCameraCore, &role->pos, dt);
}

void GameController_GUI(MainContext *ctx, float dt) {
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

    // UI: Wave
    ChapterEntity *chapter = Repository_GetChapterEntity(ctx->repository);
    const char *chapterTxt = TextFormat("Chapter: %d", chapter->chapter);
    const char *waveTxt = TextFormat("Wave: %d/%d", chapter->wave_current + 1, chapter->wave_count);
    DrawText(chapterTxt, 0, 30, 14, BLACK);
    DrawText(waveTxt, 0, 60, 14, BLACK);

    if (ChapterEntity_IsFinalWave(chapter)) {
        DrawText("Boss Wave!", 0, 90, 14, BLACK);
    }

    // UI: CD
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    Vector2Int iconPos = (Vector2Int){ctx->windowSize.x / 2 - 50, 50};
    float iconSize = 16;
    int fontSize = 16;

    // Skill1
    DrawCircleSector(Vector2Int_ToVector2(&iconPos), iconSize, 0, 360 * role->skill1_cdTimer / role->skill1_cd, 0,
                     GRAY);
    DrawCircleLines(iconPos.x, iconPos.y, iconSize, BLACK);
    DrawText("1", iconPos.x - fontSize / 4, iconPos.y - (int)iconSize / 2, fontSize, BLACK);

    // Skill2
    iconPos.x += 50;
    DrawCircleSector(Vector2Int_ToVector2(&iconPos), iconSize, 0, 360 * role->skill2_cdTimer / role->skill2_cd, 0,
                     GRAY);
    DrawCircleLines(iconPos.x, iconPos.y, iconSize, BLACK);
    DrawText("2", iconPos.x - fontSize / 4, iconPos.y - (int)iconSize / 2, fontSize, BLACK);

    // Skill3
    iconPos.x += 50;
    DrawCircleSector(Vector2Int_ToVector2(&iconPos), iconSize, 0, 360 * role->skill3_cdTimer / role->skill3_cd, 0,
                     GRAY);
    DrawCircleLines(iconPos.x, iconPos.y, iconSize, BLACK);
    DrawText("3", iconPos.x - fontSize / 4, iconPos.y - (int)iconSize / 2, fontSize, BLACK);
}

// ==== Event ====
void GameController_OnUpgradeChosen(MainContext *ctx, Enum_UpgradeOptionType opt) {
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    if (opt == Enum_UpgradeOptionType_BulletAtk) {
        role->attr_bulletAtkAddition += 1;
    } else if (opt == Enum_UpgradeOptionType_GunCooldown) {
        role->gun_cooldown *= 0.5f;
    } else if (opt == Enum_UpgradeOptionType_MoveSpeed) {
        role->move_speed += 5;
    }
}