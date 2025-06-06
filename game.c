#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "font.h"
#include "config.h"
#include "player.h"
#include "objects.h"
#include "place.h"

PageType page_type = LANDING_PAGE;
static SDL_Rect new_game = {SCREEN_WIDTH * 20/160, SCREEN_HEIGHT * 54/160, SCREEN_WIDTH * 119/160, SCREEN_WIDTH * 12/160};
static SDL_Rect cat_travers = {SCREEN_WIDTH * -12 /160, SCREEN_HEIGHT * 8/160, SCREEN_WIDTH * 58/160, SCREEN_WIDTH * 51/160};
static SDL_Rect not_eat_donuts = {SCREEN_WIDTH * 9/160, SCREEN_HEIGHT * 39/160, SCREEN_WIDTH * 140/160, SCREEN_WIDTH * 8/160};
static SDL_Rect last_score_rect = {SCREEN_WIDTH * 27/160, SCREEN_HEIGHT * 84/160, SCREEN_WIDTH * 59/160, SCREEN_WIDTH * 7/160};
static SDL_Rect nb_last_score_rect = {SCREEN_WIDTH * 89/160, SCREEN_HEIGHT * 83/160, SCREEN_WIDTH * 10/160, SCREEN_WIDTH * 9/160};
static SDL_Rect re_play = {SCREEN_WIDTH * 52/160, SCREEN_HEIGHT * 122/160, SCREEN_WIDTH * 51/160, SCREEN_WIDTH * 8/160};
static SDL_Rect credits = (SDL_Rect){SCREEN_WIDTH * 14/160, SCREEN_HEIGHT * 151/160, SCREEN_WIDTH * 124/160, SCREEN_WIDTH * 3/160};
SDL_Rect full_donuts[NB_DONUTS_MENU];

PageType get_page_type() {
    return page_type;
}

void change_page_type(PageType new_page_type) {
    page_type = new_page_type;
}

void update_game(float delta_time) {
    if (page_type == GAME_PAGE) {
        update_objects(delta_time);
    }
    update_full_donuts(delta_time);
}

void render_game(SDL_Renderer *renderer) {
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // Gris foncé
    SDL_RenderClear(renderer);

    switch (page_type)
    {
    case GAME_PAGE:
        render_player(renderer);
        render_objects(renderer);
        break;

    case LANDING_PAGE:
        render_landing_page(renderer);
        break;
    
    case RESUME_PAGE:
        render_resume_page(renderer);
        break;

    default:
        break;
    }

    SDL_RenderPresent(renderer);
}

void render_landing_page(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, bg, NULL, NULL);
    render_full_donuts(renderer, donut);
    SDL_RenderCopy(renderer, get_key_words_texture(1), NULL, &new_game);
    SDL_RenderCopy(renderer, get_key_words_texture(4), NULL, &credits);
    SDL_RenderCopyEx(renderer, cat, NULL, &cat_travers, -45, NULL, SDL_FLIP_NONE);
}

void render_resume_page(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, bg, NULL, NULL);
    render_full_donuts(renderer, donut);
    SDL_RenderCopy(renderer, get_key_words_texture(3), NULL, &not_eat_donuts);
    SDL_RenderCopy(renderer, get_key_words_texture(2), NULL, &last_score_rect);
    render_number(renderer, get_score(), &nb_last_score_rect, 5);
    SDL_RenderCopy(renderer, get_key_words_texture(1), NULL, &re_play);
}

void init_full_donuts() {
    for (int i=0; i<16; i++) {
        for (int j=0; j<8; j++) {
            full_donuts[i+16*j].x = (i*SCREEN_WIDTH/16) -15 + rand()%30;
            full_donuts[i+16*j].y = ((j-1)*SCREEN_HEIGHT/6) -50 + rand()%100;
            full_donuts[i+16*j].w = SCREEN_WIDTH * 1/16;
            full_donuts[i+16*j].h = SCREEN_WIDTH * 1/16;
        }
    }
}

void render_full_donuts(SDL_Renderer *renderer, SDL_Texture *texture) {
    for (int i=0; i<NB_DONUTS_MENU; i++) {
        SDL_RenderCopy(renderer, texture, NULL, &full_donuts[i]);
    }
}

void update_full_donuts(float dt) {
    for (int i=0; i<NB_DONUTS_MENU; i++) {
        if (full_donuts[i].y < SCREEN_HEIGHT) {
           full_donuts[i].y += (int)(SPEED * dt);
        }
        else {
            full_donuts[i].y = -SCREEN_HEIGHT/6;
        }
    }
}

void init_all(SDL_Renderer *renderer){
    srand(time(NULL));
    init_font();
    init_player(renderer);
    init_objects(renderer);
    init_full_donuts();
    load_numbers(renderer);
    load_key_words(renderer);

    reset_timer1();
}

/* GESTION DU TEMPS */
clock_t timer1;
clock_t timer2;

void reset_timer2() {
    timer2 = clock();
}

int get_timer2() {
    /* en ?s mais assez rapide */
    return (int)(1000.0 * (clock() - timer2) / CLOCKS_PER_SEC);
}

void reset_timer1() {
    timer1 = clock();
}

int get_timer1() {
    /* en ?s mais assez rapide */
    return (int)(1000.0 * (clock() - timer1) / CLOCKS_PER_SEC);
}
