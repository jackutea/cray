#ifndef __INPUTCORE_H__
#define __INPUTCORE_H__

#include <raylib.h>

typedef struct {
    Vector2 moveAxis;
} InputCore;

InputCore* InputCore_Create();
void InputCore_Tick(InputCore* inputCore);
void InputCore_TearDown(InputCore* inputCore);

#endif // __INPUTCORE_H__