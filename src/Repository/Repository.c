#include "Repository.h"
#include <stdlib.h>

Repository *Repository_New(int maxMonsterSize, int maxBulletSize) {
    Repository *repository = (Repository *)malloc(sizeof(Repository));
    repository->roleEntity = NULL;

    repository->chapterEntity = NULL;

    repository->monsters = (MonsterEntity *)calloc(maxMonsterSize, sizeof(MonsterEntity));
    repository->lastMonsterIndex = 0;

    repository->bullets = (BulletEntity *)calloc(maxBulletSize, sizeof(BulletEntity));
    repository->lastBulletIndex = 0;

    return repository;
}

void Repository_TearDown(Repository *repository) {
    free(repository);
}

// ==== Chapter ====
ChapterEntity *Repository_GetChapterEntity(Repository *repository) {
    return repository->chapterEntity;
}

void Repository_SetChapterEntity(Repository *repository, ChapterEntity *chapterEntity) {
    repository->chapterEntity = chapterEntity;
}

// ==== Role ====
RoleEntity *Repository_GetRoleEntity(Repository *repository) {
    return repository->roleEntity;
}

void Repository_SetRoleEntity(Repository *repository, RoleEntity *roleEntity) {
    repository->roleEntity = roleEntity;
}

// ==== Monster ====
MonsterEntity *Repository_GetMonsterEntity(Repository *repository, int id) {
    MonsterEntity *monsters = repository->monsters;
    int lastMonsterIndex = repository->lastMonsterIndex;
    for (int i = 0; i < lastMonsterIndex; i++) {
        if (monsters[i].id == id) {
            return &monsters[i];
        }
    }
    return 0x00;
}

void Repository_AddMonsterEntity(Repository *repository, MonsterEntity monsterEntity) {
    repository->monsters[repository->lastMonsterIndex] = monsterEntity;
    repository->lastMonsterIndex++;
}

void Repository_RemoveMonsterEntity(Repository *repository, int id) {
    MonsterEntity *monsters = repository->monsters;
    int lastMonsterIndex = repository->lastMonsterIndex;
    for (int i = 0; i < lastMonsterIndex; i++) {
        if (monsters[i].id == id) {
            monsters[i] = monsters[lastMonsterIndex - 1];
            lastMonsterIndex--;
            break;
        }
    }
    repository->lastMonsterIndex = lastMonsterIndex;
}

// ==== Bullet ====
BulletEntity *Repository_GetBulletEntity(Repository *repository, int id) {
    BulletEntity *bullets = repository->bullets;
    int lastBulletIndex = repository->lastBulletIndex;
    for (int i = 0; i < lastBulletIndex; i++) {
        if (bullets[i].id == id) {
            return &bullets[i];
        }
    }
    return 0x00;
}

void Repository_AddBulletEntity(Repository *repository, BulletEntity bulletEntity) {
    repository->bullets[repository->lastBulletIndex] = bulletEntity;
    repository->lastBulletIndex++;
}

void Repository_RemoveBulletEntity(Repository *repository, int id) {
    BulletEntity *bullets = repository->bullets;
    int lastBulletIndex = repository->lastBulletIndex;
    for (int i = 0; i < lastBulletIndex; i++) {
        if (bullets[i].id == id) {
            bullets[i] = bullets[lastBulletIndex - 1];
            lastBulletIndex--;
            break;
        }
    }
    repository->lastBulletIndex = lastBulletIndex;
}
