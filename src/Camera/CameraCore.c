#include "CameraCore.h"
#include <raymath.h>

CameraCore *CameraCore_New() {

    CameraCore *mainCameraCore = (CameraCore *)calloc(1, sizeof(CameraCore));

    RayCamera camera = (RayCamera){0};
    camera.target = (Vector2){0};
    camera.offset = (Vector2){0};
    camera.rotation = 0;
    camera.zoom = 1;
    mainCameraCore->camera = camera;

    return mainCameraCore;
}

void CameraCore_TearDown(CameraCore *mainCameraCore) {
    free(mainCameraCore);
}

void CameraCore_Begin(CameraCore *mainCameraCore, const Vector2Int *screenSize) {
    RayCamera *cam = &mainCameraCore->camera;
    cam->offset = (Vector2){screenSize->x / 2.0f, screenSize->y / 2.0f};
    BeginMode2D(*cam);
}

void CameraCore_End(CameraCore *mainCameraCore) {
    EndMode2D();
}

void CameraCore_Follow(CameraCore *mainCameraCore, const Vector2 *target, float dt) {
    RayCamera *cam = &mainCameraCore->camera;
    Vector2 shakeOffset = (Vector2){0};
    if (mainCameraCore->shakeMaintain > 0) {
        if (mainCameraCore->shakeLevel == 1) {
            shakeOffset = (Vector2){GetRandomValue(-2, 2), GetRandomValue(-2, 2)};
        } else {
            shakeOffset = (Vector2){GetRandomValue(-5, 5), GetRandomValue(-5, 5)};
        }
    }
    cam->target = Vector2Add(*target, shakeOffset);
    mainCameraCore->shakeMaintain -= dt;
    if (mainCameraCore->shakeMaintain < 0) {
        mainCameraCore->shakeMaintain = 0;
    }
}