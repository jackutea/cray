#ifndef __DRAWUTILS_H__
#define __DRAWUTILS_H__

#include <raylib.h>

#include "../GameDefines.h"

inline void DrawUtils_PercentRing(Vector2 center, float radius, int value, int valueMax, Color color) {
    DrawRing(center, radius * 0.9f, radius + 2.0f, 0, 360.0f * value / valueMax, 0, color);
}

#endif // __DRAWUTILS_H__