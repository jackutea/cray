#include <raylib.h>
#include "Math/Vector2Int.h"
#include "Input/InputCore.h"
#include "Camera/CameraCore.h"
#include "Entities/RoleEntity.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#define string const char *

static int c_add(lua_State *ls) {
    int a = luaL_checknumber(ls, 1);
    int b = luaL_checknumber(ls, 2);
    lua_pushnumber(ls, a + b);
    return 1;
}

int value = 0;
static int c_draw_int(lua_State *ls) {
    lua_getglobal(ls, "v");
    int v = lua_tonumber(ls, -1);
    value = v;
    return 1;
}

int main() {

    lua_State *ls = luaL_newstate();
    luaL_openlibs(ls);
    lua_pushcfunction(ls, c_add);
    lua_setglobal(ls, "add");
    lua_pushcfunction(ls, c_draw_int);
    lua_setglobal(ls, "draw_int");
    int status = luaL_dofile(ls, "main.lua");
    lua_close(ls);

    // ==== Instantiate ====
    InputCore *inputCore = InputCore_New();
    CameraCore *cameraCore = CameraCore_New();

    RoleEntity *role = RoleEntity_New();
    RoleEntity_Init(role, 100, 96);

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

        CameraCore_Follow(cameraCore, RoleEntity_GetPos(role));

        CameraCore_End(cameraCore);
        // ----------------

        // ==== Draw UI ====
        DrawFPS(0, 0);
        string txt = TextFormat("%d", value);
        DrawText(txt, 500, 500, 14, RED);

        EndDrawing();
    }

    // Cleanup
    RoleEntity_TearDown(role);
    InputCore_TearDown(inputCore);
    CameraCore_TearDown(cameraCore);

    CloseWindow();
    return 0;
}