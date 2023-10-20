#include "GameController.h"

void GameController_Update(MainContext *ctx, float dt) {
}

void GameController_FixedUpdate(MainContext *ctx, float fixdt) {
    InputCore *inputCore = ctx->inputCore;
    RoleEntity *role = ctx->roleEntity;
    RoleEntity_Move(role, inputCore->moveAxis, fixdt);
}

void GameController_DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt) {
    RoleEntity *role = ctx->roleEntity;
    DrawCircleV((Vector2){0}, 10, BLUE);
    RoleEntity_Draw(role);
    CameraCore_Follow(mainCameraCore, RoleEntity_GetPos(role));
}

void GameController_GUI(MainContext *ctx, float dt) {

    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    // Draw Mousepos
    Vector2 mousePos = ctx->inputCore->mouseWorldPos;
    DrawText(TextFormat("MouseWorldPos: (%.2f, %.2f)", mousePos.x, mousePos.y), 0, 20, 20, BLACK);

    // RolePos
    RoleEntity *role = ctx->roleEntity;
    const Vector2 *rolePos = RoleEntity_GetPos(role);
    DrawText(TextFormat("RolePos: (%.2f, %.2f)", rolePos->x, rolePos->y), 0, 40, 20, BLACK);
}