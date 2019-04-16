// Lesson 2
// Draw points, lines and rectangles

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

    int obx = 200;
    int oby = 810;

    int ob2x = 400;
    int ob2y =1110;

    bool running = true;

    SDL_Event event;
    while(running){
        // Process events
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RIGHT){
                    x += 10;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    x -= 10;
                }
                /*if(event.key.keysym.sym == SDLK_DOWN){
                    y += 10;
                }
                if(event.key.keysym.sym == SDLK_UP){
                    y -= 10;
                }*/
            }
        }

        if(x < wallWidth || x > width - wallWidth - 20){
            x = 390;
            y = 50;
        }
        oby -= 5;
        ob2y -= 5;
        if(oby < -50){
            oby = 600;
        }
        if(ob2y < -50){
            ob2y = 600;
        }
        if(x + 20 >= obx && x <= obx + 200){
            if(oby >= 50 && oby <= 100){
               x = 390;
            y = 50;
            }
        }
        if(x + 20 >= ob2x && x <= ob2x + 200){
            if(ob2y >= 50 && ob2y <= 100){
               x = 390;
            y = 50;
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
        SDL_Rect rect2 = {obx, oby, 200, 50};
        SDL_RenderFillRect(renderer, &rect2);

        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_Rect rect3 = {ob2x, ob2y, 200, 50};
        SDL_RenderFillRect(renderer, &rect3);

        // Show what was drawn
        SDL_RenderPresent(renderer);
    }

    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
