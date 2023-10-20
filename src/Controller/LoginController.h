#ifndef __LOGINCONTROLLER_H__
#define __LOGINCONTROLLER_H__

#include "../Context/MainContext.h"

void LoginController_Enter(MainContext *ctx);
void LoginController_Exit(MainContext *ctx);
void LoginController_Update(MainContext *ctx, float dt);
void LoginController_GUI(MainContext *ctx);

#endif // __LOGINCONTROLLER_H__