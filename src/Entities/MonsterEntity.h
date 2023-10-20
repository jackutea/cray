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
    float radius;
    float move_speed;
    Color color;
    Vector2 pos;
    Vector2 move_dir;
} MonsterEntity;

void MonsterEntity_FromTM(MonsterEntity *entity, MonsterEntity *tm);
void MonsterEntity_FaceTo(MonsterEntity *monster, Vector2 targetPos);
void MonsterEntity_Move(MonsterEntity *monster, float dt);
void MonsterEntity_BeHit(MonsterEntity *monster, int damage);
void MonsterEntity_Draw(MonsterEntity *monster);

#endif // __MONSTER_ENTITY_H__