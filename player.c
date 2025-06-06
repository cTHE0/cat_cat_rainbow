#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "player.h"
#include "place.h"
#include "config.h"
#include "font.h"
#include "game.h"

SDL_Texture *cat;
SDL_Texture *bg;
SDL_Texture *red;
SDL_Texture *vermicel;
SDL_Texture *golden_vermicel;
SDL_Rect cat_rect;
SDL_Rect score_rect;
SDL_Rect nb_score;
SDL_Rect real_player_rect;
int score = 0;

SDL_Texture *type_vermicel;

void change_vermicel_type(SDL_Texture *texture) {
    type_vermicel = texture;
}

SDL_Rect get_cat_rect() {
    return real_player_rect;
}

int get_score() {
    return score;
}

void add_score(int d_score) {
    score += d_score;
}

void init_player(SDL_Renderer *renderer) {
    cat = IMG_LoadTexture(renderer, "cat.png");
    bg = IMG_LoadTexture(renderer, "bg.png");
    red = IMG_LoadTexture(renderer, "red.png");
    vermicel = IMG_LoadTexture(renderer, "vermicel.png");
    type_vermicel = vermicel;
    golden_vermicel = IMG_LoadTexture(renderer, "golden_vermicel.png");
    cat_rect = (SDL_Rect){SCREEN_WIDTH * 0 / 160, SCREEN_HEIGHT * 106 / 160, SCREEN_WIDTH * 29 / 160, SCREEN_WIDTH * 24 / 160};
    score_rect = (SDL_Rect){SCREEN_WIDTH * 6 /160, SCREEN_HEIGHT * 0/160, SCREEN_WIDTH * 16/160, SCREEN_WIDTH * 6/160};
    nb_score = (SDL_Rect){SCREEN_WIDTH * 24 /160, SCREEN_HEIGHT * 1/160, SCREEN_WIDTH * 3/160, SCREEN_WIDTH * 6/160};
    real_player_rect = (SDL_Rect){SCREEN_WIDTH * 21/160, cat_rect.y * 181/160, SCREEN_WIDTH * 7/160, SCREEN_WIDTH * 5/160};
}

void render_player(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, bg, NULL, NULL);
    render_full_donuts(renderer, type_vermicel);
    SDL_RenderCopy(renderer, cat, NULL, &cat_rect);
    SDL_RenderCopy(renderer, get_key_words_texture(0), NULL, &score_rect);
    render_number(renderer, score, &nb_score, 4);
}

void change_y_player(int dy) {
    if (SCREEN_HEIGHT > cat_rect.y + 6*cat_rect.h/10 + dy && cat_rect.y + 4*cat_rect.h/10 + dy > 0){
        cat_rect.y += dy;
    }
    real_player_rect.y = cat_rect.y * 181/160;
}

void free_player() {
    SDL_DestroyTexture(cat);
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(red);
    SDL_DestroyTexture(vermicel);
    SDL_DestroyTexture(golden_vermicel);
}