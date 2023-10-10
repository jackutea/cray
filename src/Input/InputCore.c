#include <stdlib.h>
#include "InputCore.h"

InputCore* InputCore_Create() {
    InputCore* inputCore = malloc(sizeof(InputCore));
    inputCore->moveAxis = (Vector2){0, 0};
    return inputCore;
}

void InputCore_Tick(InputCore* inputCore) {
    inputCore->moveAxis = (Vector2){0, 0};
    if (IsKeyDown(KEY_W)) {
        inputCore->moveAxis.y -= 1;
    }
    if (IsKeyDown(KEY_S)) {
        inputCore->moveAxis.y += 1;
    }
    if (IsKeyDown(KEY_A)) {
        inputCore->moveAxis.x -= 1;
    }
    if (IsKeyDown(KEY_D)) {
        inputCore->moveAxis.x += 1;
    }
}

void InputCore_TearDown(InputCore* inputCore) {
    free(inputCore);
}