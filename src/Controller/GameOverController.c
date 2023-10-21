#include "GameOverController.h"
#include "../GUI/GUI.h"
#include "../Factory/Factory.h"

static bool isWin = false;

void ClearStage(MainContext *ctx) {

    Repository *repo = ctx->repository;

    int monsterCount = repo->lastMonsterIndex;
    for (int i = 0; i < monsterCount; i++) {
        MonsterEntity *monster = &repo->monsters[i];
        Factory_TearDownMonster(ctx, monster);
    }

    int bulletCount = repo->lastBulletIndex;
    for (int i = 0; i < bulletCount; i++) {
        BulletEntity *bullet = &repo->bullets[i];
        Factory_TearDownBullet(ctx, bullet);
    }

}
void GameOverController_EnterWin(MainContext *ctx) {
    isWin = true;
    ClearStage(ctx);
}

void GameOverController_EnterLose(MainContext *ctx) {
    isWin = false;
    ClearStage(ctx);
}

void GameOverController_Exit(MainContext *ctx) {

}

void GameOverController_GUI(MainContext *ctx, float dt) {
    const char *result = isWin ? "Win" : "Lose";
    DrawText(result, ctx->windowSize.x / 2, ctx->windowSize.y / 2, 14, BLACK);

    Rectangle rect = {ctx->windowSize.x / 2.0f, ctx->windowSize.y / 2.0f + 30, 160, 30};
    bool isClick = GUI_Button(rect, "Ok", 14, WHITE, BLACK);
    if (isClick) {
        ctx->gameStateEntity->OnGameOverClickOkHandle((void*)ctx);
    }
}