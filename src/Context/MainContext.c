#include "MainContext.h"

void MainContext_Init(MainContext *ctx, Color backgroundColor, Vector2Int windowSize, InputCore *inputCore, CameraCore *mainCameraCore, Repository *repository) {
    ctx->backgroundColor = backgroundColor;
    ctx->windowSize = windowSize;
    ctx->inputCore = inputCore;
    ctx->mainCameraCore = mainCameraCore;
    ctx->repository = repository;
}