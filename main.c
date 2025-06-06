#include <SDL2/SDL.h>
#include "game.h"
#include "config.h"
#include "event.h"
#include "font.h"
#include "player.h"
#include "objects.h"

const int TARGET_FPS = 80;
const float FRAME_DELAY = 1000.0f / TARGET_FPS;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Cat Cat Rainbow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // === Initialisation ===
    init_all(renderer);

    Uint32 last_time = SDL_GetTicks();
    SDL_bool running = SDL_TRUE;
    SDL_Event event;

    while (running) {
        Uint32 start_time = SDL_GetTicks();
        float delta_time = (start_time - last_time) / 1000.0f;
        last_time = start_time;

        gestion_event(&event, &running);

        // === Update logique ===
        update_game(delta_time);

        // === Rendu ===
        render_game(renderer);

        // Limitation du framerate
        Uint32 elapsed = SDL_GetTicks() - start_time;
        if (elapsed < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - elapsed);
        }
    }

    free_font();
    free_player();
    free_objects();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
