#include "Factory.h"
#include "../GameDefines.h"
#include <stdlib.h>

static int role_id_record = 0;
static int monster_id_record = 0;
static int bullet_id_record = 0;

RoleEntity *Factory_SpawnRole(MainContext *mainContext, int typeID, Vector2 pos, float move_speed, float radius, Color color) {

    RoleEntity *role = (RoleEntity *)malloc(sizeof(RoleEntity));
    role->id = role_id_record++;
    role->typeID = typeID;
    role->pos = pos;
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

MonsterEntity *Factory_SpawnMonster(MainContext *mainContext, int typeID, Vector2 pos, float move_speed, float radius, Color color) {

    MonsterEntity *monster = (MonsterEntity *)malloc(sizeof(MonsterEntity));
    monster->id = monster_id_record++;
    monster->typeID = typeID;
    monster->pos = pos;
    monster->move_dir = Vector2Zero();
    monster->move_speed = move_speed * PPU;
    monster->radius = radius * PPU;
    monster->color = color;

    // Repository
    Repository_AddMonsterEntity(mainContext->repository, monster);

    return monster;

}

BulletEntity *Factory_SpawnBullet(MainContext *mainContext, int typeID, Vector2 pos, Vector2 move_dir, float move_speed, float radius, Color color) {

    BulletEntity *bullet = (BulletEntity *)malloc(sizeof(BulletEntity));
    bullet->id = bullet_id_record++;
    bullet->typeID = typeID;
    bullet->pos = pos;
    bullet->move_dir = move_dir;
    bullet->move_speed = move_speed * PPU;
    bullet->radius = radius * PPU;
    bullet->color = color;

    // Repository
    Repository_AddBulletEntity(mainContext->repository, bullet);

    return bullet;

}