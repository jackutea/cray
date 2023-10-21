#include "GameOverController.h"
#include "../GUI/GUI.h"

static bool isWin = false;
void GameOverController_EnterWin(MainContext *ctx) {
    isWin = true;
}

void GameOverController_EnterLose(MainContext *ctx) {
    isWin = false;
}

void GameOverController_Exit(MainContext *ctx) {

}

void GameOverController_GUI(MainContext *ctx, float dt) {
    const char *result = isWin ? "Win" : "Lose";
    DrawText(result, ctx->windowSize.x / 2.0f, ctx->windowSize.y / 2.0f, 14, BLACK);

    Rectangle rect = {ctx->windowSize.x / 2.0f, ctx->windowSize.y / 2.0f + 30, 160, 30};
    bool isClick = GUI_Button(rect, "Ok", 14, WHITE, BLACK);
    if (isClick) {
        ctx->gameStateEntity->OnGameOverClickOkHandle((void*)ctx);
    }
}