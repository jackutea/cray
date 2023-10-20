#include "ChapterEntity.h"

void ChapterEntity_FromTM(ChapterEntity *entity, ChapterEntity *tm) {
    entity->chapter = tm->chapter;
    entity->boss_typeID = tm->boss_typeID;
    entity->wave_monster_level = tm->wave_monster_level;
    entity->wave_monster_count = tm->wave_monster_count;
    entity->wave_current = 0;
    entity->wave_count = tm->wave_count;
}

void ChapterEntity_ScaleAliveRadius(ChapterEntity *chapter, float dt) {
    chapter->aliveRadius -= chapter->alive_scale_speed * dt;
}

void ChapterEntity_Draw(ChapterEntity *chapter) {
    DrawCircleV((Vector2){0, 0}, chapter->aliveRadius, (Color){240, 240, 240, 255});
}