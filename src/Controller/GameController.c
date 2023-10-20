#include "GameController.h"
#include "../Factory/Factory.h"

void GameController_Enter(MainContext *ctx) {
    // Role: Spawn
    Factory_SpawnRole(ctx, 1, (Vector2){0}, 5.0f, 1.0f, BLUE);
}

void GameController_Update(MainContext *ctx, float dt) {

    // Role: Rotate
    // Role: Shoot

    // Bullet: Spawn
    
}

void GameController_FixedUpdate(MainContext *ctx, float fixdt) {

    // God: Spawn Monster

    // Role: Move
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    RoleEntity_Move(role, ctx->inputCore->moveAxis, fixdt);

    // Bullet: Move

    // Monster: Move

    // Hit: Role -> Monster
    // Hit: Bullet -> Monster

}

void GameController_DrawMainCamera(MainContext *ctx, CameraCore *mainCameraCore, float dt) {
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    DrawCircleV((Vector2){0}, 10, BLUE);
    RoleEntity_Draw(role);
    CameraCore_Follow(mainCameraCore, &role->pos);
}

void GameController_GUI(MainContext *ctx, float dt) {

    SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    // Draw Mousepos
    Vector2 mousePos = ctx->inputCore->mouseWorldPos;
    DrawText(TextFormat("MouseWorldPos: (%.2f, %.2f)", mousePos.x, mousePos.y), 0, 20, 20, BLACK);

    // RolePos
    RoleEntity *role = Repository_GetRoleEntity(ctx->repository);
    const Vector2 *rolePos = &role->pos;
    DrawText(TextFormat("RolePos: (%.2f, %.2f)", rolePos->x, rolePos->y), 0, 40, 20, BLACK);
}