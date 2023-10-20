#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "../Context/MainContext.h"

void GameController_Enter(MainContext *ctx);
void GameController_Update(MainContext *ctx, float dt);
void GameController_FixedUpdate(MainContext *ctx, float fixdt);
void GameController_DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt);
void GameController_GUI(MainContext *ctx, float dt);

#endif // __GAME_CONTROLLER_H__