#ifndef OBJECTS_H
#define OBJECTS_H

#include <SDL2/SDL.h>

extern SDL_Texture *donut;
extern SDL_Texture *gift;

typedef enum { DONUT, GIFT } ObjectType;

typedef struct {
    SDL_Rect rect;
    SDL_Rect hitbox;
    ObjectType type;
    int id;
} Object;

void init_objects(SDL_Renderer *renderer);

void render_objects(SDL_Renderer *renderer);

void update_objects(float dt);

void collision();

void delete_all_objects();

void free_objects();

#endif
