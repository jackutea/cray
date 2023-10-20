#ifndef __GAMESTATEENTITY_H__
#define __GAMESTATEENTITY_H__

typedef enum Enum_GameStatus {
    Enum_GameStatus_Ready = 1,
    Enum_GameStatus_Playing = 2,
    Enum_GameStatus_Paused = 3,
    Enum_GameStatus_GameOver = 4,
    Enum_GameStatus_Win = 5
} Enum_GameStatus;

typedef struct {
    Enum_GameStatus status;
    void (*OnLoginClickStartGameHandle)(void*);
} GameStateEntity;

#endif // __GAMESTATEENTITY_H__