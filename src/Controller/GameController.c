#include "GameController.h"
#include "../Domain/RoleDomain.h"
#include "../Domain/HitDomain.h"
#include "../Factory/Factory.h"

Vector2 GetSpawnPosByDir(MainContext *ctx, EnumFromDir dir) {
    Vector2Int pos;
    Vector2Int half = (Vector2Int){.x = ctx->windowSize.x / 2, .y = ctx->windowSize.y / 2};
    if (dir == EnumFromDir_Left) {
        pos.x = -half.x;
        pos.y = GetRandomValue(-half.y, half.y);
    } else if (dir == EnumFromDir_Right) {
        pos.x = half.x;
        pos.y = GetRandomValue(-half.y, half.y);
    } else if (dir == EnumFromDir_Top) {
        pos.x = GetRandomValue(-half.x, half.x);
        pos.y = -half.y;
    } else if (dir == EnumFromDir_Bottom) {
        pos.x = GetRandomValue(-half.x, half.x);
        pos.y = half.y;
    }
    return Vector2Int_ToVector2(&pos);
}

Vector2 GetRandomSpawnPosDir(MainContext *ctx) {
    EnumFromDir dir = (EnumFromDir)GetRandomValue(0, 3);
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
            int curMonsterLevel = chapter->wave_monster_level[chapter->wave_current];
            int curMonsterCount = chapter->wave_monster_count[chapter->wave_current];
            for (int i = 0; i < curMonsterCount; i += 1) {
                Factory_SpawnMonsterByLevel(ctx, curMonsterLevel, GetRandomSpawnPosDir(ctx));
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

    // Bullet: Move
    BulletEntity *bullets = ctx->repository->bullets;
    int lastBulletIndex = ctx->repository->lastBulletIndex;
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        BulletEntity_Move(bullet, fixdt);
    }

    // Monster: Move
    MonsterEntity *monsters = ctx->repository->monsters;
    int lastMonsterIndex = ctx->repository->lastMonsterIndex;
    for (int i = 0; i < lastMonsterIndex; i++) {
        MonsterEntity *monster = &monsters[i];
        MonsterEntity_FaceTo(monster, role->pos);
        MonsterEntity_Move(monster, fixdt);
    }

    // Hit: Monster -> Role

    // Hit: Bullet -> Monster
    for (int i = 0; i < lastBulletIndex; i++) {
        BulletEntity *bullet = &bullets[i];
        for (int j = 0; j < lastMonsterIndex; j++) {
            MonsterEntity *monster = &monsters[j];
            HitDomain_BulletHitMonster(ctx, bullet, monster);
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

    CameraCore_Follow(mainCameraCore, &role->pos);
}

void GameController_GUI(MainContext *ctx, float dt) {
    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
}