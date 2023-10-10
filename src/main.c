#include <raylib.h>
#include "Input/InputCore.h"
#include "Entities/RoleEntity.h"

#define string const char*

int main() {

    // ==== Instantiate ====
    InputCore* inputCore = InputCore_Create();

    RoleEntity* role = RoleEntity_Create();

    // ==== Inject ====

    // ==== Pre Init ====

    // ==== Init ====

    // ==== Enter ====

    InitWindow(960, 540, "Hello World");

    Color bg = WHITE;

    SetTargetFPS(144);

    // ==== Tick ====
    while (!WindowShouldClose()) {

        float delta_time = GetFrameTime();

        // ==== Process Input ====
        InputCore_Tick(inputCore);

        // ==== Do Logic ====
        RoleEntity_Move(role, inputCore->moveAxis, delta_time);

        // ==== Draw ====
        BeginDrawing();

        // - Sky Blue Background
        ClearBackground(bg);

        // - Entities
        DrawCircleV(role->pos, 10, RED);

        // - UI
        DrawFPS(0, 0);

        EndDrawing();
    }

    // Cleanup
    RoleEntity_TearDown(role);
    InputCore_TearDown(inputCore);

    CloseWindow();
    return 0;
}