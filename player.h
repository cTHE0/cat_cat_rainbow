#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

extern SDL_Texture *bg;
extern SDL_Texture *cat;
extern SDL_Texture *red;
extern SDL_Texture *vermicel;
extern SDL_Texture *golden_vermicel;

SDL_Rect get_cat_rect();

void change_vermicel_type(SDL_Texture *texture);

int get_score();

void add_score(int d_score);

void init_player(SDL_Renderer *renderer);

void render_player(SDL_Renderer *renderer);

void change_y_player(int mouse);

void free_player();

#endif
