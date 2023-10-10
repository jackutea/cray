#include <stdlib.h>
#include "InputCore.h"

InputCore* InputCore_Create() {
    InputCore* inputCore = calloc(1, sizeof(InputCore));
    return inputCore;
}

void InputCore_Tick(InputCore* inputCore) {
    Vector2 moveAxis = inputCore->moveAxis;
    moveAxis = (Vector2){0, 0};
    if (IsKeyDown(KEY_W)) {
        moveAxis.y -= 1;
    }
    if (IsKeyDown(KEY_S)) {
        moveAxis.y += 1;
    }
    if (IsKeyDown(KEY_A)) {
        moveAxis.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        moveAxis.x += 1;
    }
    inputCore->moveAxis = moveAxis;
}

void InputCore_TearDown(InputCore* inputCore) {
    free(inputCore);
}