#ifndef __GAMESTATEENTITY_H__
#define __GAMESTATEENTITY_H__

#include "../GameDefines.h"

typedef struct {
    Enum_GameStatus status;
    void (*OnLoginClickStartGameHandle)();
    void (*OnGameUpgradeHandle)(Enum_UpgradeOptionType, Enum_UpgradeOptionType, Enum_UpgradeOptionType);
    void (*OnGameWinHandle)();
    void (*OnGameLoseHandle)();
    void (*OnGameOverClickOkHandle)();
} GameStateEntity;

#endif // __GAMESTATEENTITY_H__