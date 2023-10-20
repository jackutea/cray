#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "../Context/MainContext.h"

ChapterEntity *Factory_SpawnChapter(MainContext *mainContext, int chapter);
RoleEntity *Factory_SpawnRole(MainContext *mainContext, int typeID, Vector2 pos, float move_speed, float radius, Color color);
MonsterEntity *Factory_SpawnMonster(MainContext *mainContext, int typeID, Vector2 pos, float move_speed, float radius, Color color);
BulletEntity *Factory_SpawnBullet(MainContext *mainContext, int typeID, Vector2 pos, Vector2 move_dir, float move_speed, float radius, Color color);

#endif // __FACTORY_H__