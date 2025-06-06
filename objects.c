#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "objects.h"
#include "list.h"
#include "config.h"
#include "game.h"
#include "player.h"
#include "math.h"
#include "place.h"

Node *objects = NULL;

SDL_Texture *donut;
SDL_Texture *gift;

SDL_Rect hitbox;

void init_objects(SDL_Renderer *renderer) {
    donut = IMG_LoadTexture(renderer, "donut.png");
    gift = IMG_LoadTexture(renderer, "gift.png");
}

void render_objects(SDL_Renderer *renderer) {
    Node *local_list = objects;
    while (local_list != NULL) {
        if (local_list->data.type == DONUT) {
            SDL_RenderCopy(renderer, donut, NULL, &local_list->data.rect);
        }
        else {
            SDL_RenderCopy(renderer, gift, NULL, &local_list->data.rect);
        }
        local_list = local_list->next;
    }
}

void update_objects(float dt) {
    Node *local_list = objects;

    Node **current = &local_list;
    int time_local = get_timer2();
    while (*current != NULL) {
        (*current)->data.rect.x -= SPEED * 0.02 * time_local * dt;
        (*current)->data.hitbox.x -= SPEED * 0.02 * time_local * dt;

        if ((*current)->data.rect.x + (*current)->data.rect.w < 0) {
            Node *to_delete = *current;
            *current = to_delete->next;
            free(to_delete); // supprimer ici directement au lieu de deleteById
            add_score(1);

        } else {
            current = &(*current)->next;
        }
    }

    // Ajout d'un objet toutes les x secondes
    if (get_timer1() > SPEED / (get_timer2() * 0.012)) {
        reset_timer1();

        int y = (rand() % 20) * (SCREEN_HEIGHT) / 20  -  SCREEN_WIDTH/8;
        int id = find_unused_id(local_list);

        Object new_object;
        if (rand() % 10 == 0) {
            new_object = (Object){(SDL_Rect){SCREEN_WIDTH, y, SCREEN_WIDTH / 15, SCREEN_WIDTH / 15}, (SDL_Rect){0, 0, 0, 0}, GIFT, id};
        } else {
            new_object = (Object){(SDL_Rect){SCREEN_WIDTH, y, SCREEN_WIDTH / 4, SCREEN_WIDTH / 4}, (SDL_Rect){0, 0, 0, 0}, DONUT, id};
            new_object.hitbox = (SDL_Rect){new_object.rect.x + 0.2*new_object.rect.w, new_object.rect.y + 0.15*new_object.rect.h, 0.6*new_object.rect.w, 0.7*new_object.rect.h};

        }

        append(&local_list, new_object);
    }

    // Mettre à jour la liste globale à la fin
    objects = local_list;
    collision();
}

void delete_all_objects() {
    freeList(objects);
    objects = NULL;
}

void collision(){
    Node *local_list = objects;
    SDL_Rect catcat = get_cat_rect();

    Node **current = &local_list;
    while (*current != NULL) {
        if (((*current)->data.type == DONUT) && SDL_HasIntersection(&catcat, &(*current)->data.hitbox)) {
            change_page_type(RESUME_PAGE);
        }
        else if (((*current)->data.type == GIFT) && SDL_HasIntersection(&catcat, &(*current)->data.rect)){
            change_vermicel_type(golden_vermicel);
        }
        current = &(*current)->next;
    }
}

void free_objects() {
    SDL_DestroyTexture(gift);
    SDL_DestroyTexture(donut);
}