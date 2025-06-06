#include <SDL2/SDL.h>
#include "event.h"
#include "place.h"
#include "player.h"
#include "game.h"
#include "objects.h"

SDL_bool is_down;
SDL_Point mouse;

void gestion_event(SDL_Event *event, SDL_bool *running){
    while (SDL_PollEvent(event)) {
       SDL_GetMouseState(&mouse.x, &mouse.y);
        switch (event->type)
        {
        case SDL_QUIT:
            *running = SDL_FALSE;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            is_down = SDL_TRUE;
            if (get_page_type() == LANDING_PAGE || get_page_type() == RESUME_PAGE) {
                add_score(-get_score());
                delete_all_objects();
                change_page_type(GAME_PAGE);
                reset_timer2();
            }
            break;

        case SDL_MOUSEBUTTONUP:
            is_down = SDL_FALSE;
            break;
        
        case SDL_MOUSEMOTION:
            if (is_down) {
                    //modify_rect(-event->motion.xrel, -event->motion.yrel);
                    change_y_player(event->motion.yrel);
                }
            break;
        
        /*---------Partie pr développement------------*/

        case SDL_KEYDOWN:
                switch (event->key.keysym.sym)
                {
                case SDLK_1:
                    change_sign();
                    break;
                case SDLK_x:
                    modif_emp(1, 0, 0, 0);
                    break;
                case SDLK_y:
                    modif_emp(0, 1, 0, 0);
                    break;
                case SDLK_w:
                    modif_emp(0, 0, 1, 0);
                    break;
                case SDLK_h:
                    modif_emp(0, 0, 0, 1);
                    break;
                }
                
                break;

        /*---------Partie pr développement------------*/


        default:
            break;
        }
    }
}