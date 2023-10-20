#include "MainContext.h"

void MainContext_Init(MainContext *ctx, Color backgroundColor, Vector2Int windowSize, InputCore *inputCore, CameraCore *mainCameraCore, RoleEntity *roleEntity) {
    ctx->backgroundColor = backgroundColor;
    ctx->windowSize = windowSize;
    ctx->inputCore = inputCore;
    ctx->mainCameraCore = mainCameraCore;
    ctx->roleEntity = roleEntity;
}