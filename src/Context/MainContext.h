#ifndef __MAINCONTEXT_H__
#define __MAINCONTEXT_H__

#include <raylib.h>
#include "../Math/Vector2Int.h"
#include "../Input/InputCore.h"
#include "../Camera/CameraCore.h"
#include "../Entities/RoleEntity.h"
#include "../Entities/GameStateEntity.h"
#include "../Repository/Repository.h"
#include "../Template/Templates.h"

typedef struct {
    GameStateEntity *gameStateEntity;
    Color backgroundColor;
    Vector2Int windowSize;
    InputCore *inputCore;
    CameraCore *mainCameraCore;
    Repository *repository;
    Templates *templates;
} MainContext;

void MainContext_Inject(MainContext *ctx, GameStateEntity *gameStateEntity, Color backgroundColor, Vector2Int windowSize, InputCore *inputCore,
                      CameraCore *mainCameraCore, Repository *repository, Templates *templates);

#endif