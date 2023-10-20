#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "../Context/MainContext.h"

ChapterEntity *Factory_SpawnChapter(MainContext *mainContext, int chapter);
RoleEntity *Factory_SpawnRole(MainContext *mainContext, int typeID, Vector2 pos);
void Factory_SpawnMonster(MainContext *mainContext, int typeID, Vector2 pos);
void Factory_SpawnMonsterByLevel(MainContext *mainContext, int level, Vector2 pos);
void Factory_SpawnBullet(MainContext *mainContext, int typeID, Vector2 pos, Vector2 move_dir);

#endif // __FACTORY_H__