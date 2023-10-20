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
    int monster_typeID;
    int monster_count;
    EnumFromDir enum_from_dir;
} MonsterDescModel;

typedef struct {
    int wave;
    int cur_monster_desc;
    MonsterDescModel *monster_descs;
    int monster_desc_count;
} ChapterWaveComponent;

typedef struct {
    int chapter;
    int cur_wave;
    ChapterWaveComponent *waves;
    int wave_count;
} ChapterEntity;

#endif // __CHAPTERENTITY_H__