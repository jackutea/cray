#ifndef __GUN_COMPONENT_H__
#define __GUN_COMPONENT_H__

#include <raylib.h>

typedef struct {
    float cooldown;
    float cooldownTimer;
    float bulletRadius;
    float bulletSpeed;
    Color bulletColor;
} GunComponent;

#endif // __GUN_COMPONENT_H__