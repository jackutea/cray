#include "ChapterEntity.h"
#include <math.h>

void ChapterEntity_FromTM(ChapterEntity *entity, ChapterEntity *tm) {
    entity->chapter = tm->chapter;
    entity->boss_typeID = tm->boss_typeID;
    entity->wave_monster_level = tm->wave_monster_level;
    entity->wave_monster_count = tm->wave_monster_count;
    entity->wave_current = 0;
    entity->wave_count = tm->wave_count;
}

bool ChapterEntity_IsFinalWave(ChapterEntity *chapter) {
    return chapter->wave_current == chapter->wave_count - 1;
}

void ChapterEntity_NextWave(ChapterEntity *chapter) {
    chapter->wave_current++;
    if (chapter->wave_current >= chapter->wave_count) {
        chapter->wave_current = chapter->wave_count - 1;
    }
}

void ChapterEntity_ScaleAliveRadius(ChapterEntity *chapter, float dt) {
    chapter->aliveRadius -= chapter->alive_scale_speed * dt;
}

void ChapterEntity_Draw(ChapterEntity *chapter) {

    DrawCircle(0, 0, chapter->aliveRadius, (Color){230, 230, 230, 255});

    // Draw Grid
    float gap = 300;
    // for (int i = -50; i < 50; i++) {
    //     Vector2 start = (Vector2){i * gap, -5000};
    //     Vector2 end = (Vector2){i * gap, 5000};
    //     DrawLineV(start, end, (Color){200, 200, 200, 255});

    //     start = (Vector2){-5000, i * gap};
    //     end = (Vector2){5000, i * gap};
    //     DrawLineV(start, end, (Color){200, 200, 200, 255});
    // }

    // Draw Alive Radius
    for (int i = 1; i <= 10; i += 1) {
        DrawCircleLines(0, 0, i * gap, (Color){255, 255, 255, 255});
    }

    // UI: Wave
    const char *chapterTxt = TextFormat("Chapter: %d", chapter->chapter);
    const char *waveTxt = TextFormat("Wave: %d/%d", chapter->wave_current + 1, chapter->wave_count);
    DrawText(chapterTxt, 0, 30, 14, BLACK);
    DrawText(waveTxt, 0, 60, 14, BLACK);

    if (ChapterEntity_IsFinalWave(chapter)) {
        DrawText("Boss Wave!", 0, 90, 14, BLACK);
    }
}