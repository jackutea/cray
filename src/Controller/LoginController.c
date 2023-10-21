#include "LoginController.h"
#include "../GUI/GUI.h"

void LoginController_Enter(MainContext *ctx) {
}

void LoginController_Exit(MainContext *ctx) {
}

void LoginController_Update(MainContext *ctx, float dt) {

}

void LoginController_GUI(MainContext *ctx) {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    Rectangle rect = {100, 100, 160, 30};
    DrawText(GAME_NAME, rect.x, rect.y, 18, BLACK);
    rect.y += 30;
    bool isClick = GUI_Button(rect, "Start Game", 14, WHITE, BLACK);
    if (isClick) {
        ctx->gameStateEntity->OnLoginClickStartGameHandle((void*)ctx);
    }
}

