#ifndef GAME_H
#define GAME_H

typedef enum { LANDING_PAGE, GAME_PAGE, RESUME_PAGE } PageType;

void change_page_type(PageType new_page_type);
PageType get_page_type();
void render_landing_page(SDL_Renderer *renderer);
void render_resume_page(SDL_Renderer *renderer);
void update_game(float delta_time);
void render_game(SDL_Renderer *renderer);
void init_all(SDL_Renderer *renderer);
void init_full_donuts();
void render_full_donuts(SDL_Renderer *renderer, SDL_Texture *texture);
void update_full_donuts(float dt);
void reset_timer1();
int get_timer1();
void reset_timer2();
int get_timer2();

#endif
