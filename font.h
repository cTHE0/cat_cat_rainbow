#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

TTF_Font* loadFont(const char* fontPath, int fontSize);
void init_font();
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color);
void renderText(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect);
void load_numbers(SDL_Renderer* renderer);
void render_number(SDL_Renderer *renderer, int i, SDL_Rect *dstRect, int nb_chiffres);
void free_font();
void load_key_words(SDL_Renderer *renderer);
SDL_Texture *get_key_words_texture(int i);