#include "CameraCore.h"

CameraCore *CameraCore_New() {

    CameraCore *cameraCore = (CameraCore *)calloc(1, sizeof(CameraCore));

    RayCamera camera = (RayCamera){0};
    camera.target = (Vector2){0};
    camera.offset = (Vector2){0};
    camera.rotation = 0;
    camera.zoom = 1;
    cameraCore->camera = camera;

    return cameraCore;
}

void CameraCore_TearDown(CameraCore *cameraCore) {
    free(cameraCore);
}

void CameraCore_Begin(CameraCore *cameraCore, const Vector2Int *screenSize) {
    RayCamera *cam = &cameraCore->camera;
    cam->offset = (Vector2){screenSize->x / 2.0f, screenSize->y / 2.0f};
    BeginMode2D(*cam);
}

void CameraCore_End(CameraCore *cameraCore) {
    EndMode2D();
}

void CameraCore_Follow(CameraCore *cameraCore, const Vector2 *target) {
    RayCamera *cam = &cameraCore->camera;
    cam->target = *target;
}