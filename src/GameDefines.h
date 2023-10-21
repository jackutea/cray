#ifndef __GAME_DEFINES_H__
#define __GAME_DEFINES_H__

#include <raylib.h>

#define string const char *

#define COLOR_HP CLITERAL(Color){ 37, 37, 37, 255 }

static string GAME_NAME = "Cycle Survivor";

static const float PPU = 16.0f;
static const int ENUM_NONE = 0;

typedef enum Enum_GameStatus {
    Enum_GameStatus_Ready = 1,
    Enum_GameStatus_Playing = 2,
    Enum_GameStatus_Paused = 3,
    Enum_GameStatus_Upgrade = 4,
    Enum_GameStatus_GameOver = 5,
    Enum_GameStatus_Win = 6
} Enum_GameStatus;

typedef enum Enum_FromDir {
    Enum_FromDir_Left = 0,
    Enum_FromDir_Right = 1,
    Enum_FromDir_Top = 2,
    Enum_FromDir_Bottom = 3
} Enum_FromDir;

typedef enum Enum_BulletFlyType {
    Enum_BulletFlyType_Linear = 1,
    Enum_BulletFlyType_TopDown = 2,
} Enum_BulletFlyType;

typedef enum Enum_UpgradeOptionType {
    Enum_UpgradeOptionType_None = 0,
    Enum_UpgradeOptionType_BulletAtk = 1,
    Enum_UpgradeOptionType_GunCooldown = 2,
    Enum_UpgradeOptionType_MoveSpeed = 3,
} Enum_UpgradeOptionType;

#endif // __GAME_DEFINES_H__