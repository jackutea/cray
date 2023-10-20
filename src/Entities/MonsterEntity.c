#include "MonsterEntity.h"
#include <raymath.h>

void MonsterEntity_Move(MonsterEntity *monster, float dt) {
    Vector2 dir = monster->move_dir;
    dir = Vector2Normalize(dir);
    dir = Vector2Scale(dir, monster->move_speed * dt);
    monster->pos = Vector2Add(monster->pos, dir);
}

void MonsterEntity_FaceTo(MonsterEntity *monster, Vector2 targetPos) {
    Vector2 dir = Vector2Subtract(targetPos, monster->pos);
    dir = Vector2Normalize(dir);
    if (dir.x != 0 && dir.y != 0) {
        monster->move_dir = dir;
    } else {
        monster->move_dir = (Vector2){0, -1};
    }
}

void MonsterEntity_Draw(MonsterEntity *monster) {
    DrawCircleV(monster->pos, monster->radius, monster->color);
}