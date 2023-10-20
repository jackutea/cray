#include "MainContext.h"

void MainContext_Init(MainContext *ctx, Color backgroundColor, Vector2Int windowSize, InputCore *inputCore,
                      CameraCore *mainCameraCore, Repository *repository, Templates *templates) {
    ctx->backgroundColor = backgroundColor;
    ctx->windowSize = windowSize;
    ctx->inputCore = inputCore;
    ctx->mainCameraCore = mainCameraCore;
    ctx->repository = repository;
    ctx->templates = templates;
}