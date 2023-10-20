#ifndef __CHAPTERENTITY_H__
#define __CHAPTERENTITY_H__

#include <raylib.h>

typedef enum EnumFromDir {
    EnumFromDir_Left = 0,
    EnumFromDir_Right = 1,
    EnumFromDir_Top = 2,
    EnumFromDir_Bottom = 3
} EnumFromDir;

typedef struct {
    int chapter;
    int boss_typeID;
    int *wave_monster_level;
    int *wave_monster_count;
    int wave_current;
    int wave_count;
    float wave_timer;
    float aliveRadius;
    float alive_scale_speed;
} ChapterEntity;

bool ChapterEntity_IsFinalWave(ChapterEntity *chapter);
void ChapterEntity_NextWave(ChapterEntity *chapter);
void ChapterEntity_FromTM(ChapterEntity *chapter, ChapterEntity *tm);
void ChapterEntity_ScaleAliveRadius(ChapterEntity *chapter, float dt);
void ChapterEntity_Draw(ChapterEntity *chapter);

#endif // __CHAPTERENTITY_H__