#include <stdlib.h>
#include "InputCore.h"
#include <raymath.h>

InputCore *InputCore_New() {
    InputCore *inputCore = calloc(1, sizeof(InputCore));
    return inputCore;
}

void InputCore_Tick(InputCore *inputCore, Camera2D *camera) {
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

    Vector2 mousePos = inputCore->mouseScreenPos;
    mousePos = GetMousePosition();
    inputCore->mouseScreenPos = mousePos;

    Vector2 mouseWorldPos = inputCore->mouseWorldPos;
    mouseWorldPos = GetScreenToWorld2D(mousePos, *camera);
    inputCore->mouseWorldPos = mouseWorldPos;

    inputCore->isMouseLeftDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    inputCore->isMouseRightDown = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
}

void InputCore_ClearCurrentFrame(InputCore *inputCore) {
    inputCore->isMouseLeftDown = false;
    inputCore->isMouseRightDown = false;
    inputCore->mouseScreenPos = Vector2Zero();
    inputCore->mouseWorldPos = Vector2Zero();
    inputCore->moveAxis = Vector2Zero();
}

void InputCore_TearDown(InputCore *inputCore) {
    free(inputCore);
}