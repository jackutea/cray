#include "Context/MainContext.h"
#include "Controller/GameController.h"

#define string const char *
const float FIXED_DELTA_TIME = 0.01f;
float rest_time = 0.0f;

void FixedUpdate(MainContext *ctx, float fixdt);
void Update(MainContext *ctx, float dt);
void DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt);
void GUI(MainContext *ctx, float dt);
void TearDown(MainContext *ctx);

int main() {

    MainContext ctx;

    Color bg = WHITE;
    Vector2Int windowSize = (Vector2Int){960, 540};

    // ==== Instantiate ====
    InputCore *inputCore = InputCore_New();
    CameraCore *mainCameraCore = CameraCore_New();
    Repository *repository = Repository_New(500, 2000);

    // ==== Inject ====

    // ==== Pre Init ====

    // ==== Init ====
    InitWindow(windowSize.x, windowSize.y, "Hello World");
    SetExitKey(KEY_PAUSE);
    SetTargetFPS(120);

    MainContext_Init(&ctx, bg, windowSize, inputCore, mainCameraCore, repository);

    // ==== Enter ====
    GameController_Enter(&ctx);

    // ==== Tick ====
    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        Update(&ctx, dt); // Update && FixedUpdate

        BeginDrawing();
        DrawMainCamera(&ctx, ctx.mainCameraCore, dt); // Draw One Camera
        GUI(&ctx, dt); // UI
        EndDrawing();
    }

    // Cleanup
    TearDown(&ctx);

    CloseWindow();
    return 0;
}

void Update(MainContext *ctx, float dt) {

    // ==== Process Input ====
    InputCore *inputCore = ctx->inputCore;
    InputCore_Tick(inputCore, &ctx->mainCameraCore->camera);

    GameController_Update(ctx, dt);

    // ==== Do Logic ====
    rest_time += dt;
    if (rest_time < FIXED_DELTA_TIME) {
        FixedUpdate(ctx, rest_time);
    } else {
        for (; rest_time >= FIXED_DELTA_TIME; rest_time -= FIXED_DELTA_TIME) {
            FixedUpdate(ctx, FIXED_DELTA_TIME);
        }
    }
}

void FixedUpdate(MainContext *ctx, float fixdt) {
    GameController_FixedUpdate(ctx, fixdt);
}

void DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt) {
    CameraCore_Begin(mainCameraCore, &ctx->windowSize);

    ClearBackground(ctx->backgroundColor);

    GameController_DrawMainCamera(ctx, mainCameraCore, dt);

    CameraCore_End(mainCameraCore);
}

void GUI(MainContext *ctx, float dt) {
    GameController_GUI(ctx, dt);
    DrawFPS(0, 0);
}

void TearDown(MainContext *ctx) {
    Repository *repository = ctx->repository;
    free(repository->monsters);
    free(repository->bullets);
    free(repository->roleEntity);
    free(repository);
    InputCore_TearDown(ctx->inputCore);
    CameraCore_TearDown(ctx->mainCameraCore);
}