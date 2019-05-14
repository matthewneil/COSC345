#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

//#include "utils.h"

static const int width = 800;
static const int height = 600;
static TTF_Font *font = NULL;
static SDL_Renderer *renderer;

/*
void displayText(TTF_Font *font, char *message, SDL_Color colour, SDL_Rect rectangle){
    //SDL_Color textColor = colour;
    SDL_RenderClear(renderer);
    SDL_Surface* mainMessage = TTF_RenderText_Solid(font, message, colour);
    SDL_Texture* mainMessage2 = SDL_CreateTextureFromSurface(renderer, mainMessage);
    SDL_RenderCopy(renderer, mainMessage2, NULL, rectangle);
    SDL_RenderPresent(renderer);
}*/


int main(int argc, char **argv){
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Raymond Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_JPG);
    TTF_Init();

    float x = 390;
    float y = 50;
    int wallWidth = 200;

    //int obx = 200;
    float oby = 810;
    float speed = 3;

    int points = 0;
    int counted1 = 0;
    int counted2 = 0;

    float ob2y = 1110;

    float obx = (rand() % 320)+200;
    float ob2x = (rand() % 350)+200;
    float ob3x = (rand() % 300)+200;

    float ob4x = (rand() % 320)+200;
    float ob5x = (rand() % 350)+200;
    float ob6x = (rand() % 300)+200;

    SDL_Rect MainMenu_rect;
    MainMenu_rect.x = 250;
    MainMenu_rect.y = 285;
    MainMenu_rect.w = 300;
    MainMenu_rect.h = 30;

    SDL_Rect wall_rect;
    wall_rect.x = 0;
    wall_rect.y = 0;
    wall_rect.w = 200;
    wall_rect.h = 600;

    SDL_Rect wall_rect2 = wall_rect;
    wall_rect2.x = 600;

    SDL_Rect wall_rect1_2 = wall_rect;
    wall_rect1_2.y = 600;

    SDL_Rect wall_rect2_2 = wall_rect2;
    wall_rect2_2.y = 600;

    SDL_Rect background_rect;
    background_rect.x = 0;
    background_rect.y = 0;
    background_rect.w = 800;
    background_rect.h = 600;

    SDL_Rect background_rect2 = background_rect;
    background_rect.y = 600;

    bool running = true;
    bool move_left = false;
    bool move_right = false;
    bool move_up = false;
    bool move_down = false;
    SDL_Event event;
    bool main_menu = true;
    bool gameOver = false;


    SDL_Color textColor = { 255, 0, 255 };
    //Open the font
    font = TTF_OpenFont( "/Windows/Fonts/Arial.ttf", 28 );

    SDL_Surface *image = IMG_Load("wall.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_Surface *background = IMG_Load("stonebackground.png");
    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(renderer, background);

    while(running){

        if (main_menu == true){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            oby = 810;
            speed = 3;
            points = 0;
            counted1 = 0;
            counted2 = 0;
            ob2y = 1110;
            x = 390;
            y = 50;
            move_right = false;
            move_left = false;
            move_up = false;
            move_down = false;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    main_menu = false;
                }
            }

            SDL_Color textColor = { 255, 255, 255 };
            SDL_RenderClear(renderer);
            SDL_Surface* mainMessage = TTF_RenderText_Solid(font, "Press space bar to start!", textColor);
            SDL_Texture* mainMessage2 = SDL_CreateTextureFromSurface(renderer, mainMessage);
            SDL_RenderCopy(renderer, mainMessage2, NULL, &MainMenu_rect);
            SDL_RenderPresent(renderer);
            //displayText(font, "Press Spacebar to start!", textColor, &MainMenu_rect);

        } else if (gameOver == true){

        } else {

            if(event.type == SDL_QUIT){
                running = false;
            }
            while(SDL_PollEvent(&event)){
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







            //SDL_RenderPresent(renderer);

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

            if(!font){
                return false;
            }

            SDL_Rect Message_rect; //create a rect
            Message_rect.x = 300;  //controls the rect's x coordinate
            Message_rect.y = 0; // controls the rect's y coordinte
            Message_rect.w = 20; // controls the width of the rect
            Message_rect.h = 20;

            SDL_Rect Message_rect2; //create a rect
            Message_rect2.x = 250;  //controls the rect's x coordinate
            Message_rect2.y = 0; // controls the rect's y coordinte
            Message_rect2.w = 50; // controls the width of the rect
            Message_rect2.h = 20;



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
                   main_menu = true;
                }
            }
            if(x + 20 >= ob2x && x <= ob2x + 50){
                if(oby + 50 >= y && oby <= y+50){
                   main_menu = true;
                }
            }

            if(x + 20 >= ob3x && x <= ob3x + 100){
                if(oby + 50 >= y && oby <= y+50){
                   main_menu = true;
                }
            }

            if(x + 20 >= ob4x && x <= ob4x + 70){
                if(ob2y + 50 >= y && ob2y <= y+50){
                   main_menu = true;
                }
            }
            if(x + 20 >= ob5x && x <= ob5x + 50){
                if(ob2y + 50 >= y && ob2y <= y+50){
                   main_menu = true;
                }
            }

            if(x + 20 >= ob6x && x <= ob6x + 100){
                if(ob2y + 50 >= y && ob2y <= y+50){
                   main_menu = true;
                }
            }



            // Clear screen with black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            background_rect.y -= 2;
            if(background_rect.y <= -600){
                background_rect.y = 600;
            }
            SDL_RenderCopy(renderer, backTexture, NULL, &background_rect);

            background_rect2.y -= 2;
            if(background_rect2.y <= -600){
                background_rect2.y = 600;
            }
            SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);
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

            char array[64];
            sprintf(array, "%d", points);
            printf("%s\n", array);

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, array, textColor); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
            SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(font, "Score: ", textColor);

            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

            SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);

            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
            // Show what was drawn
            wall_rect.y -= 3;
            if(wall_rect.y <= -600){
                wall_rect.y = 600;
            }
            SDL_RenderCopy(renderer, texture, NULL, &wall_rect);

            wall_rect2.y -= 3;
            if(wall_rect2.y <= -600){
                wall_rect2.y = 600;
            }
            SDL_RenderCopy(renderer, texture, NULL, &wall_rect2);

            wall_rect1_2.y -= 3;
            if(wall_rect1_2.y <= -600){
                wall_rect1_2.y = 600;
            }
            SDL_RenderCopy(renderer, texture, NULL, &wall_rect1_2);

            wall_rect2_2.y -= 3;
            if(wall_rect2_2.y <= -600){
                wall_rect2_2.y = 600;
            }
            SDL_RenderCopy(renderer, texture, NULL, &wall_rect2_2);
            // Show what was drawn
            SDL_RenderPresent(renderer);
        }


    }

    TTF_CloseFont(font);

    TTF_Quit();
    IMG_Quit();
    // Release resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


