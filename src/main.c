#include "Context/MainContext.h"
#include "Controller/GameController.h"
#include "Controller/GameOverController.h"
#include "Controller/LoginController.h"

static const float FIXED_DELTA_TIME = 0.01f;
static float rest_time = 0.0f;

// Life Cycle
void Update(MainContext *ctx, float dt);
void FixedUpdate(MainContext *ctx, float fixdt);
void LateUpdate(MainContext *ctx, float dt);
void DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt);
void GUI(MainContext *ctx, float dt);
void TearDown(MainContext *ctx);

// Event: Controller
void OnLoginClickStartGame();
void OnGameUpgrade(Enum_UpgradeOptionType opt1, Enum_UpgradeOptionType opt2, Enum_UpgradeOptionType opt3);
void OnGameWin();
void OnGameLose();
void OnGameOverClickOk();

// Event: UI
void OnGameUpgradeChosen(Enum_UpgradeOptionType opt);

static MainContext *ctx;

int main() {

    ctx = calloc(1, sizeof(MainContext));

    Color bg = WHITE;
    Vector2Int windowSize = (Vector2Int){960, 540};

    // ==== Instantiate ====
    GameStateEntity *gameStateEntity = calloc(1, sizeof(GameStateEntity));
    InputCore *inputCore = InputCore_New();
    CameraCore *mainCameraCore = CameraCore_New();
    Repository *repository = Repository_New(500, 2000);
    Templates *templates = Templates_New();
    UpgradeUI *upgradeUI = UpgradeUI_New();

    // ==== Inject ====
    ctx->gameStateEntity = gameStateEntity;
    ctx->backgroundColor = bg;
    ctx->windowSize = windowSize;
    ctx->inputCore = inputCore;
    ctx->mainCameraCore = mainCameraCore;
    ctx->repository = repository;
    ctx->templates = templates;
    ctx->upgradeUI = upgradeUI;

    // ==== Pre Init ====
    gameStateEntity->status = Enum_GameStatus_Ready;

    // ==== Init ====
    InitWindow(windowSize.x, windowSize.y, "Hello World");
    SetExitKey(KEY_PAUSE);
    SetTargetFPS(120);

    Templates_Init(templates);

    // ==== Binding Event ====
    gameStateEntity->OnLoginClickStartGameHandle = &OnLoginClickStartGame;
    gameStateEntity->OnGameUpgradeHandle = &OnGameUpgrade;
    gameStateEntity->OnGameWinHandle = &OnGameWin;
    gameStateEntity->OnGameLoseHandle = &OnGameLose;
    gameStateEntity->OnGameOverClickOkHandle = &OnGameOverClickOk;

    upgradeUI->OnUpgradeChosenHandle = &OnGameUpgradeChosen;

    // ==== Enter ====
    LoginController_Enter(ctx);

    // ==== Tick ====
    while (!WindowShouldClose()) {

        // ctx.windowSize.x = GetScreenWidth();
        // ctx.windowSize.y = GetScreenHeight();

        float dt = GetFrameTime();

        Update(ctx, dt); // Update && FixedUpdate
        LateUpdate(ctx, dt); // LateUpdate

        BeginDrawing();
        DrawMainCamera(ctx, ctx->mainCameraCore, dt); // Draw One Camera
        GUI(ctx, dt);                                // UI
        EndDrawing();
    }

    // Cleanup
    TearDown(ctx);

    CloseWindow();
    return 0;
}

void Update(MainContext *ctx, float dt) {

    // ==== Process Input ====
    InputCore *inputCore = ctx->inputCore;
    InputCore_ClearCurrentFrame(inputCore);
    InputCore_Tick(inputCore, &ctx->mainCameraCore->camera);

    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    Enum_GameStatus status = gameStateEntity->status;
    if (status == Enum_GameStatus_Playing) {
        GameController_Update(ctx, dt);
    } else if (status == Enum_GameStatus_Ready) {
        LoginController_Update(ctx, dt);
    }

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
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    Enum_GameStatus status = gameStateEntity->status;
    if (status == Enum_GameStatus_Playing) {
        GameController_FixedUpdate(ctx, fixdt);
    } else if (status == Enum_GameStatus_Ready) {
    }
}

void LateUpdate(MainContext *ctx, float dt) {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    Enum_GameStatus status = gameStateEntity->status;
    if (status == Enum_GameStatus_Playing) {
        GameController_LateUpdate(ctx, dt);
    } else if (status == Enum_GameStatus_Ready) {
    } else if (status == Enum_GameStatus_GameOver) {
        
    }
}

void DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt) {
    CameraCore_Begin(mainCameraCore, &ctx->windowSize);

    ClearBackground(ctx->backgroundColor);

    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    Enum_GameStatus status = gameStateEntity->status;
    if (status == Enum_GameStatus_Playing) {
        GameController_DrawMainCamera(ctx, mainCameraCore, dt);
    } else if (status == Enum_GameStatus_Ready) {
    } else if (status == Enum_GameStatus_GameOver) {

    }

    CameraCore_End(mainCameraCore);
}

void GUI(MainContext *ctx, float dt) {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    Enum_GameStatus status = gameStateEntity->status;
    if (status == Enum_GameStatus_Playing) {
        GameController_GUI(ctx, dt);
    } else if (status == Enum_GameStatus_Ready) {
        LoginController_GUI(ctx);
    } else if (status == Enum_GameStatus_GameOver) {
        GameOverController_GUI(ctx, dt);
    } else if (status == Enum_GameStatus_Upgrade) {
        UpgradeUI_GUI(ctx->upgradeUI);
    }
    DrawFPS(0, 0);
}

void TearDown(MainContext *ctx) {
    Repository *repository = ctx->repository;
    free(repository->monsters);
    free(repository->bullets);
    RoleEntity_TearDown(repository->roleEntity);
    free(repository);
    InputCore_TearDown(ctx->inputCore);
    CameraCore_TearDown(ctx->mainCameraCore);
    free(ctx);
}

// ==== Event ====
// Controller
void OnLoginClickStartGame() {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_Playing;
    GameController_Enter(ctx);
}

void OnGameUpgrade(Enum_UpgradeOptionType opt1, Enum_UpgradeOptionType opt2, Enum_UpgradeOptionType opt3) {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_Upgrade;
    UpgradeUI_Open(ctx->upgradeUI, opt1, opt2, opt3);
}

void OnGameWin() {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_GameOver;
    GameOverController_EnterWin(ctx);
}

void OnGameLose() {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_GameOver;
    GameOverController_EnterLose(ctx);
}

void OnGameOverClickOk() {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_Ready;
    LoginController_Enter(ctx);
}

// UI
void OnGameUpgradeChosen(Enum_UpgradeOptionType opt) {
    GameStateEntity *gameStateEntity = ctx->gameStateEntity;
    gameStateEntity->status = Enum_GameStatus_Playing;
    GameController_OnUpgradeChosen(ctx, opt);
}