#include <raylib.h>
#include "Math/Vector2Int.h"
#include "Input/InputCore.h"
#include "Camera/CameraCore.h"
#include "Entities/RoleEntity.h"

#define string const char *

int main() {

    // ==== Instantiate ====
    InputCore *inputCore = InputCore_New();
    CameraCore *cameraCore = CameraCore_New();

    RoleEntity *role = RoleEntity_New();

    // ==== Inject ====

    // ==== Pre Init ====

    // ==== Init ====

    // ==== Enter ====
    Vector2Int screenSize = (Vector2Int){960, 540};

    InitWindow(screenSize.x, screenSize.y, "Hello World");

    Color bg = WHITE;

    SetTargetFPS(144);

    // ==== Tick ====
    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        // ==== Process Input ====
        InputCore_Tick(inputCore);

        // ==== Do Logic ====
        RayCamera *cam = &cameraCore->camera;
        RoleEntity_Move(role, inputCore->moveAxis, delta_time);

        BeginDrawing();

        // ==== Draw World ====
        // - Sky Background
        ClearBackground(bg);

        // ---- Camera ----
        CameraCore_Begin(cameraCore, &screenSize);

        // - Entities
        DrawCircleV((Vector2){0}, 10, BLUE);
        RoleEntity_Draw(role);

        CameraCore_Follow(cameraCore, &role->pos);

        CameraCore_End(cameraCore);
        // ----------------

        // ==== Draw UI ====
        DrawFPS(0, 0);

        EndDrawing();
    }

    // Cleanup
    RoleEntity_TearDown(role);
    InputCore_TearDown(inputCore);
    CameraCore_TearDown(cameraCore);

    CloseWindow();
    return 0;
}