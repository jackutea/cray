#ifndef __INPUTCORE_H__
#define __INPUTCORE_H__

#include <raylib.h>

typedef struct {
    Vector2 moveAxis;
    Vector2 mouseScreenPos;
    Vector2 mouseWorldPos;
    bool isMouseLeftDown;
    bool isMouseRightDown;
} InputCore;

InputCore *InputCore_New();
void InputCore_Tick(InputCore *inputCore, Camera2D *camera);
void InputCore_TearDown(InputCore *inputCore);
void InputCore_ClearCurrentFrame(InputCore *inputCore);

#endif // __INPUTCORE_H__