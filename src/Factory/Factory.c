#include "Factory.h"
#include "../GameDefines.h"
#include <stdlib.h>

RoleEntity *Factory_SpawnRole(MainContext *mainContext, int id, Vector2 position, float move_speed, float radius, Color color) {

    RoleEntity *role = (RoleEntity *)malloc(sizeof(RoleEntity));
    role->id = id;
    role->pos = position;
    role->move_speed = move_speed * PPU;
    role->radius = radius * PPU;
    role->color = color;

    GunComponent gunCom;
    gunCom.bulletColor = BLACK;
    gunCom.bulletRadius = 0.1f * PPU;
    gunCom.bulletSpeed = 5.0f * PPU;
    gunCom.cooldown = 0.5f;
    gunCom.cooldownTimer = 0.0f;
    role->gunCom = gunCom;

    // Repository
    Repository_SetRoleEntity(mainContext->repository, role);

    return role;

}