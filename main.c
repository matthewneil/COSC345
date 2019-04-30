#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
//#include "utils.h"

static const int width = 800;
static const int height = 600;

int main(int argc, char **argv)
{
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Raymond Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int x = 390;
    int y = 50;
    int wallWidth = 200;

    //int obx = 200;
    int oby = 810;
    int speed = 3;

    int points = 0;
    int counted1 = 0;
    int counted2 = 0;

    int ob2y = 1110;

    int obx = (rand() % 320)+200;
    int ob2x = (rand() % 350)+200;
    int ob3x = (rand() % 300)+200;

    int ob4x = (rand() % 320)+200;
    int ob5x = (rand() % 350)+200;
    int ob6x = (rand() % 300)+200;

    bool running = true;
    bool move_left = false;
    bool move_right = false;
    bool move_up = false;
    bool move_down = false;
    SDL_Event event;
    while(running){

        // Process events
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
            if(event.type == SDL_KEYUP){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    move_right = false;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    move_left = false;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    move_down = false;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    move_up = false;
                }
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    move_right = true;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    move_left = true;
                }
                if(event.key.keysym.sym == SDLK_DOWN){
                    move_down = true;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    move_up = true;
                }
            }
        }
        if(move_left){
            x -= 5;
        }
        if(move_right){
            x += 5;
        }
        if(move_up){
            y -= 5;
        }
        if(move_down){
            y += 5;
        }

        if(x < wallWidth || x > width - wallWidth - 20){
            break;
        }

        oby -= speed;
        ob2y -= speed;
        if((oby <= y-5 && counted1 == 0)){
            counted1 = 1;
            points++;
            printf("%d\n", points);
            if(points % 10 == 0){
                speed++;
            }
        }
        if((ob2y <= y-5 && counted2 == 0)){
            counted2 = 1;
            points++;
            printf("%d\n", points);
            if(points % 10 == 0){
                speed++;
            }
        }
        //ob2y -= 0.1;
        //ob3y -= 0.1;
        if(oby < -50){
            obx = (rand() % 320)+200;
            ob2x = (rand() % 350)+200;
            ob3x = (rand() % 300)+200;
            oby = 600;
            counted1 = 0;
        }
        if(ob2y < -50){
            ob4x = (rand() % 320)+200;
            ob5x = (rand() % 350)+200;
            ob6x = (rand() % 300)+200;
            ob2y = 600;
            counted2 = 0;
        }
        /*
        if(ob2y < -50){
            ob2y = 600;
        }*/
        if(y < 0){
            y = 0;
        }
        if(y > 550){
            y = 550;
        }
        if(x + 20 >= obx && x <= obx + 70){
            if(oby + 50 >= y && oby <= y+50){
               break;
            }
        }
        if(x + 20 >= ob2x && x <= ob2x + 50){
            if(oby + 50 >= y && oby <= y+50){
               break;
            }
        }

        if(x + 20 >= ob3x && x <= ob3x + 100){
            if(oby + 50 >= y && oby <= y+50){
               break;
            }
        }

        if(x + 20 >= ob4x && x <= ob4x + 70){
            if(ob2y + 50 >= y && ob2y <= y+50){
               break;
            }
        }
        if(x + 20 >= ob5x && x <= ob5x + 50){
            if(ob2y + 50 >= y && ob2y <= y+50){
               break;
            }
        }

        if(x + 20 >= ob6x && x <= ob6x + 100){
            if(ob2y + 50 >= y && ob2y <= y+50){
               break;
            }
        }


        // Clear screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

        SDL_Rect wall1 = {0, 0, 200, 600};
        SDL_RenderFillRect(renderer, &wall1);

        SDL_Rect wall2 = {600, 0, 200, 600};
        SDL_RenderFillRect(renderer, &wall2);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow color

        // Draw a rectangle
        SDL_Rect rect = {x, y, 20, 50};
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect2 = {obx, oby, 70, 50};
        SDL_RenderFillRect(renderer, &rect2);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_Rect rect3 = {ob2x, oby, 50, 50};
        SDL_RenderFillRect(renderer, &rect3);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_Rect rect4 = {ob3x, oby, 100, 50};
        SDL_RenderFillRect(renderer, &rect4);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect5 = {ob4x, ob2y, 70, 50};
        SDL_RenderFillRect(renderer, &rect5);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_Rect rect6 = {ob5x, ob2y, 50, 50};
        SDL_RenderFillRect(renderer, &rect6);

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_Rect rect7 = {ob6x, ob2y, 100, 50};
        SDL_RenderFillRect(renderer, &rect7);

        // Show what was drawn
        SDL_RenderPresent(renderer);


    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
