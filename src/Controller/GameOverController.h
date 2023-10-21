#ifndef __GAMEOVERCONTROLLER_H__
#define __GAMEOVERCONTROLLER_H__

#include "../Context/MainContext.h"

void GameOverController_EnterWin(MainContext *ctx);
void GameOverController_EnterLose(MainContext *ctx);
void GameOverController_Exit(MainContext *ctx);
void GameOverController_GUI(MainContext *ctx, float dt);

#endif // __GAMEOVERCONTROLLER_H__