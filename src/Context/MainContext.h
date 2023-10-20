#ifndef __MAINCONTEXT_H__
#define __MAINCONTEXT_H__

#include <raylib.h>
#include "../Math/Vector2Int.h"
#include "../Input/InputCore.h"
#include "../Camera/CameraCore.h"
#include "../Entities/RoleEntity.h"
#include "../Repository/Repository.h"

typedef struct {
    Color backgroundColor;
    Vector2Int windowSize;
    InputCore *inputCore;
    CameraCore *mainCameraCore;
    Repository *repository;
} MainContext;

void MainContext_Init(MainContext *ctx, Color backgroundColor, Vector2Int windowSize, InputCore *inputCore, CameraCore *mainCameraCore, Repository *repository);

#endif