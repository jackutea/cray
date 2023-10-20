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

void GameController_Enter(MainContext *ctx) {
    // Chapter: Spawn
    ChapterEntity *chapter = Factory_SpawnChapter(ctx, 1);
    // Role: Spawn
    RoleEntity *role = Factory_SpawnRole(ctx, 1, (Vector2){0});

    // TEST
    // Monster: Spawn
    Vector2 monsterSpawnPos = GetSpawnPosByDir(ctx, EnumFromDir_Left);
    Factory_SpawnMonster(ctx, 1, monsterSpawnPos);
}

void GameController_Update(MainContext *ctx, float dt) {

    // Role: Rotate
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    RoleEntity_Face(role, ctx->inputCore->mouseWorldPos);

    // Bullet: Spawn
}

void GameController_FixedUpdate(MainContext *ctx, float fixdt) {

    // God: Spawn Monster

    // Chapter: Scale Alive Radius
    ChapterEntity *chapter = Repository_GetChapterEntity(ctx->repository);
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
    // Draw Mousepos
    Vector2 mousePos = ctx->inputCore->mouseWorldPos;
    DrawText(TextFormat("MouseWorldPos: (%.2f, %.2f)", mousePos.x, mousePos.y), 0, 20, 20, BLACK);

    // RolePos
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    const Vector2 *rolePos = &role->pos;
    DrawText(TextFormat("RolePos: (%.2f, %.2f)", rolePos->x, rolePos->y), 0, 40, 20, BLACK);
}