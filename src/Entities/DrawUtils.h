#ifndef __DRAWUTILS_H__
#define __DRAWUTILS_H__

#include <raylib.h>

#include "../GameDefines.h"

inline void DrawUtils_HpRing(Vector2 center, float radius, int hp, int hpMax, Color color) {
    DrawRing(center, radius * 0.9f, radius + 2.0f, 0, 360.0f * hp / hpMax, 0, color);
}

#endif // __DRAWUTILS_H__