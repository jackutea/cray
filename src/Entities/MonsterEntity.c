#include "MonsterEntity.h"
#include <raymath.h>

void MonsterEntity_FromTM(MonsterEntity *entity, MonsterEntity *tm) {
    entity->typeID = tm->typeID;
    entity->level = tm->level;
    entity->isBoss = tm->isBoss;
    entity->attr_hp = tm->attr_hp;
    entity->attr_hpMax = tm->attr_hpMax;
    entity->attr_atk = tm->attr_atk;
    entity->radius = tm->radius;
    entity->move_speed = tm->move_speed;
    entity->color = tm->color;
}

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

void MonsterEntity_BeHit(MonsterEntity *monster, int damage) {
    monster->attr_hp -= damage;
    if (monster->attr_hp < 0) {
        monster->attr_hp = 0;
    }
}

void MonsterEntity_Draw(MonsterEntity *monster) {
    // Draw Body Inner-Outline
    DrawCircleV(monster->pos, monster->radius, BLACK);

    // Draw Body
    float innerRadius = monster->radius * 0.8f;
    DrawCircleV(monster->pos, innerRadius, monster->color);
}