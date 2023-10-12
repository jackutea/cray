#ifndef __CAMERA_CORE_H__
#define __CAMERA_CORE_H__

#include <raylib.h>
#include <stdlib.h>
#include "../Math/Vector2Int.h"

typedef Camera2D RayCamera;

typedef struct {
    RayCamera camera;
} CameraCore;

CameraCore *CameraCore_New();
void CameraCore_TearDown(CameraCore *cameraCore);
void CameraCore_Begin(CameraCore *cameraCore, const Vector2Int *screenSize);
void CameraCore_Follow(CameraCore *cameraCore, const Vector2 *target);
void CameraCore_End(CameraCore *cameraCore);

#endif