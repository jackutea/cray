#ifndef __MONSTER_ENTITY_H__
#define __MONSTER_ENTITY_H__

#include <raylib.h>

typedef struct {
    int id;
    int typeID;
    int level;
    bool isBoss;
    int attr_hp;
    int attr_hpMax;
    int attr_atk;
    Vector2 pos;
    Vector2 move_dir;
    float radius;
    float move_speed;
    Color color;
} MonsterEntity;

void MonsterEntity_FaceTo(MonsterEntity *monster, Vector2 targetPos);
void MonsterEntity_Move(MonsterEntity *monster, float dt);
void MonsterEntity_Draw(MonsterEntity *monster);

#endif // __MONSTER_ENTITY_H__