#ifndef __RAYLIBEXTENSION_H__
#define __RAYLIBEXTENSION_H__

#include <raylib.h>
#include <math.h>

inline float MyClamp(float value, float min, float max) {
    if (value <= min)
        return min;
    if (value >= max)
        return max;
    return value;
}

inline bool CheckCollisionCircleAABB(Vector2 center, float radius, Vector2 boxCenter, Vector2 boxSize) {
    Vector2 min = Vector2Subtract(boxCenter, Vector2Scale(boxSize, 0.5f));
    Vector2 max = Vector2Add(boxCenter, Vector2Scale(boxSize, 0.5f));
    Vector2 closestPoint = (Vector2){0};
    closestPoint.x = MyClamp(center.x, min.x, max.x);
    closestPoint.y = MyClamp(center.y, min.y, max.y);
    float distance = Vector2Distance(center, closestPoint);
    return distance <= radius;
}

float Vector2LengthSquared(Vector2 v) {
    return v.x * v.x + v.y * v.y;
}

// static bool IsIntersectCircle_OBB(in FPSphere2D circle, in FPOBB2D obb, in FP64 epsilon) {
//     // 1. OBB 转为 AABB 坐标系
//     // 2. 与 Circle & AABB 相同
//     FPVector2 i = obb.Center - circle.Center;
//     i = FPMath2DUtil.MulRotAndPos(new FPRotation2D(-obb.RadAngle), i);
//     FPVector2 v = FPVector2.Max(i, -i);
//     FPVector2 diff = FPVector2.Max(v - obb.Size * FP64.Half, FPVector2.Zero);
//     return (circle.Radius * circle.Radius) - diff.LengthSquared() > epsilon;
// }
inline bool CheckCollisionCircleOBB(Vector2 circleCenter, float circleRadius, Vector2 boxCenter, Vector2 boxSize,
                                    float boxRotation) {
    Vector2 i = Vector2Subtract(boxCenter, circleCenter);
    float angle = -boxRotation * DEG2RAD;
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);
    i = (Vector2){i.x * cosAngle - i.y * sinAngle, i.x * sinAngle + i.y * cosAngle};
    Vector2 v = (Vector2){fabsf(i.x), fabsf(i.y)};
    Vector2 diff = Vector2Subtract(v, Vector2Scale(boxSize, 0.5f));
    float distanceSquared = Vector2LengthSquared(diff);
    return distanceSquared <= (circleRadius * circleRadius);
}

#endif // __RAYLIBEXTENSION_H__