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
}