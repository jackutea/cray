#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "../Context/MainContext.h"

RoleEntity *Factory_SpawnRole(MainContext *mainContext, int id, Vector2 position, float move_speed, float radius, Color color);

#endif // __FACTORY_H__