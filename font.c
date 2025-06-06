#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "font.h"
#include "config.h"

SDL_Texture *number_textures[10]; // textures pour les chiffres de 0 à 9
SDL_Texture *key_words_textures[NB_KEY_WORDS];
char *key_words[NB_KEY_WORDS] = {"Scrore:", "Tap to play", "Last score:", "Eating donuts is bad for your health !", "A game by The Void Company, the creators of Space Miner!"};
TTF_Font* font = NULL;

// Fonction pour charger une police
TTF_Font* loadFont(const char* fontPath, int fontSize) {
    TTF_Font* font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    return font;
}

void init_font() {
    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur TTF_Init: %s\n", TTF_GetError());
        return;
    }

    font = loadFont("porter.ttf", 200);
    if (!font) {
        fprintf(stderr, "Erreur ouverture font\n");
    }
}

// Fonction pour créer une texture de texte
SDL_Texture* createTextTexture(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        fprintf(stderr, "Erreur TTF_RenderText_Solid: %s\n", TTF_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

// Fonction pour rendre le texte
void renderText(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect) {
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

// Préparer les textures pour les chiffres de 0 à 9
void load_numbers(SDL_Renderer* renderer) {
    char digit_str[2] = "0";
    for (int i = 0; i < 10; i++) {
        digit_str[0] = '0' + i;
        number_textures[i] = createTextTexture(renderer, font, digit_str, (SDL_Color){16, 16, 16, 255}); /* Pas noir pur pour pouvoir donner teinte rougeatre*/
    }
}

void load_key_words(SDL_Renderer *renderer) {
    for (int i=0; i<NB_KEY_WORDS; i++) {
        key_words_textures[i] = createTextTexture(renderer, font, key_words[i], (SDL_Color){16, 16, 16, 255});
    }
}

SDL_Texture *get_key_words_texture(int i) {
    return key_words_textures[i];
}

void render_number(SDL_Renderer *renderer, int i, SDL_Rect *dstRect, int nb_chiffres) {
    if (nb_chiffres <= 0 || nb_chiffres > 20) return; // Limite de sécurité

    char buffer[21]; // Assez grand pour nb_chiffres jusqu'à 20 + '\0'
    snprintf(buffer, sizeof(buffer), "%0*d", nb_chiffres, i); // Formatage avec zéros à gauche

    SDL_Rect rect = *dstRect;

    for (int j = 0; j < nb_chiffres; j++) {
        char c = buffer[j];
        if (c >= '0' && c <= '9') {
            int digit = c - '0';
            renderText(renderer, number_textures[digit], &rect);
            rect.x += rect.w; // Avance vers la droite pour le chiffre suivant
        }
    }
}


// Libération des ressources
void free_font() {
    for (int i = 0; i < 10; i++) {
        if (number_textures[i] != NULL) {
            SDL_DestroyTexture(number_textures[i]);
            number_textures[i] = NULL;
        }
    }

    for (int i=0; i<NB_KEY_WORDS; i++) {
        if (key_words_textures[i] != NULL) {
            SDL_DestroyTexture(number_textures[i]);
            key_words_textures[i] = NULL;
        }
    }

    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }

    if (TTF_WasInit()) {
        TTF_Quit();
    }
}
