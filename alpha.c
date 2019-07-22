/**
 *
 * COSC345 'Dungeon Fall' Assignment 2 2019
 * Ben Highsted, Matthew Neil, Jasmine Hindson
 *
 * Last Edited: 27/05/2019 2:39PM.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


#define TICK_INTERVAL 15

static const int width = 1000;//width and height of the window
static const int height = 700;
static Uint32 next_time;

/** Method works out how much time is left and determines how much to slow down for the current PC
 *  https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidetimeexamples.html
 **/
Uint32 time_left(void)
{
    Uint32 now;
    now = SDL_GetTicks();
    if(next_time <= now){
        return 0;
    }else{
        return next_time - now;
    }
}

int main(int argc, char **argv)
{
    next_time = SDL_GetTicks() + TICK_INTERVAL;//determines how fast the program should run
    Mix_Music *music = NULL;

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
        return false;
    }

    music = Mix_LoadMUS( "busta.mp3" );

    if( music == NULL ){
        return false;
    }

    if( Mix_PlayMusic( music, -1 ) == -1 ){
        return 1;
    }
    Mix_Chunk *keem = NULL;
    keem = Mix_LoadWAV( "keem.mp3" );

    SDL_Init(SDL_INIT_VIDEO);//Initialize SDL and creates a window/renderer
    SDL_Window *window = SDL_CreateWindow("Dungeon Fall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    IMG_Init(IMG_INIT_JPG);//Image initialisation code

    TTF_Font *font = NULL, *font2 = NULL;
    //Open the fonts
    font = TTF_OpenFont("/Windows/Fonts/Georgia.ttf", 100);
    font2 = TTF_OpenFont("/Windows/Fonts/Arial.ttf", 100);
    if(!font){
        printf("Failed to find font");
        return false;
    }

    /** Variable Declarations **/
    int score = 00000001, attempts = 0, counterAdd = 5, x = 475, y = 250;
    int startx = 300, starty = 530, fallx = 300, fally = -100, wallLeftX = -800, wallRightX = 800;
    int mode = 0, counted1 = 0, counted2 = 0, pos, phases = 0, position = 185;

    float menuCounter = 0, fallCounter = 0, backCounter = 0, backCounter2 = 0, location = 375;
    float counter = 0.0, counter2 = 0.0, counter3 = 0.0, counter4 = 0.0;
    float obx = (rand() % 520)+200, ob2x = (rand() % 550)+200, ob3x = (rand() % 500)+200;
    float ob4x = (rand() % 520)+200, ob5x = (rand() % 550)+200, ob6x = (rand() % 500)+200;
    int speed = 4, oby = 810, ob2y = 1110, wallCount = 0.0;
    float wallPos1 = 100, wallPos2 = 300, wallPos3 = 500, wallPos4 = 700;

    bool add = true, fall = false, first_loop = false, running = true;
    bool setup = true, switchModes = false, complete;
    bool move_left = false, move_right = false, move_up = false, move_down = false;
    bool main_menu = true, game_over = false, rightmove = false;
    bool character_description = false, main_menu_screen = true;
    bool sprite1 = true, sprite2 = false, sprite3 = false;

    char *array = (char *) malloc(64);
    char *array2 = (char *) malloc(64);

    SDL_Rect wall_rect = {-800, 0, 1000, 600};
    SDL_Rect wall_rect2 = wall_rect;
    wall_rect2.x = 800;
    SDL_Rect wall_rect1_2 = wall_rect;
    wall_rect1_2.y = 600;
    SDL_Rect wall_rect2_2 = wall_rect2;
    wall_rect2_2.y = 600;
    SDL_Rect Message_rect = {505, 5, 35, 20};
    SDL_Rect Message_rect2 = {450, 0, 50, 30};
    SDL_Rect MainMenu_rect = {300, 400, 400, 50};
    SDL_Rect MainMenu_rect2 = {250, 300, 500, 50};
    SDL_Rect Title_rect = {150, 50, 700, 300};
    SDL_Rect Title_background_rect = {0, 0, 1000, 700};
    SDL_Rect Title_background_rect2 = {0, 700, 1000, 700};
    SDL_Rect background_rect = {0, 0, 1000, 700};
    SDL_Rect background_rect2 = {0, 700, 1000, 700};
    SDL_Rect sprite1_rect = {200, 340, 130, 130};
    SDL_Rect sprite_rect2 = {350, 50, 220, 220};
    SDL_Rect sprite2_rect = {400, 340, 130, 130};
    SDL_Rect sprite3_rect = {600, 340, 130, 130};

    SDL_Event event;

    SDL_Surface *image = IMG_Load("bricks.png");//background and wall textures. NEED TO BE REFERENCED!!!!
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Surface *background = IMG_Load("bricksBackground.png");
    SDL_Texture *backTexture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Surface *borderSurface = IMG_Load("border.png");
    SDL_Texture *border = SDL_CreateTextureFromSurface(renderer, borderSurface);

    SDL_Surface *spriteStraightTexture = IMG_Load("sprite1straight.png");
    SDL_Texture *sprite1StraightTexture = SDL_CreateTextureFromSurface(renderer, spriteStraightTexture);
    SDL_Surface *sprite2Straight = IMG_Load("sprite2straight.png");
    SDL_Texture *sprite2StraightTexture = SDL_CreateTextureFromSurface(renderer, sprite2Straight);
    SDL_Surface *sprite3Straight = IMG_Load("sprite3straight.png");
    SDL_Texture *sprite3StraightTexture = SDL_CreateTextureFromSurface(renderer, sprite3Straight);
    SDL_Surface *spriteTexture = IMG_Load("sprite1falling.png");
    SDL_Texture *sprite1FallingTexture = SDL_CreateTextureFromSurface(renderer, spriteTexture);
    SDL_Surface *sprite2Falling = IMG_Load("sprite2falling.png");
    SDL_Texture *sprite2FallingTexture = SDL_CreateTextureFromSurface(renderer, sprite2Falling);
    SDL_Surface *sprite3Falling = IMG_Load("Sprite3falling.png");
    SDL_Texture *sprite3FallingTexture = SDL_CreateTextureFromSurface(renderer, sprite3Falling);

    SDL_Surface *fireRed = IMG_Load("fireRed.png");
    SDL_Texture *fireRedTexture = SDL_CreateTextureFromSurface(renderer, fireRed);
    SDL_Surface *fireBlue = IMG_Load("fireBlue.png");
    SDL_Texture *fireBlueTexture = SDL_CreateTextureFromSurface(renderer, fireBlue);
    SDL_Surface *fireGreen = IMG_Load("fireGreen.png");
    SDL_Texture *fireGreenTexture = SDL_CreateTextureFromSurface(renderer, fireGreen);

    SDL_Surface* surfaceMessage;
    SDL_Surface* surfaceMessage2;
    SDL_Texture* Message;
    SDL_Texture* Message2;

    while(running){

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;

        if(event.type == SDL_QUIT){
            running = false;
        }
        if(main_menu == true){
            if(character_description == true) {
                SDL_RenderClear(renderer);
                SDL_Rect nameRect = {300, 280, 300, 50};
                SDL_Rect descriptionRect = {10, 350, 980, 30};
                SDL_Rect infoRect = {370, 550, 200, 30};

                SDL_Color textColor = {255, 255, 255};

                SDL_Texture* sprite = NULL;
                SDL_Surface* nameSurface = NULL;
                SDL_Texture* nameTexture = NULL;
                SDL_Surface* descriptionSurface = NULL;
                SDL_Texture* descriptionTexture = NULL;
                SDL_Surface* infoSurface = TTF_RenderText_Solid(font, "Press backspace", textColor);
                SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(renderer, infoSurface);

                if(sprite1 == true) {
                    sprite = sprite1StraightTexture;
                    nameSurface = TTF_RenderText_Solid(font, "Andrew the ...", textColor);
                    nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
                    descriptionSurface = TTF_RenderText_Solid(font, "Write here about Andrew, maybe the story of how he has fallen in the hole? Something funny to make the game COOL", textColor);
                    descriptionTexture = SDL_CreateTextureFromSurface(renderer, descriptionSurface);
                } else if (sprite2 == true) {
                    sprite = sprite2StraightTexture;
                    nameSurface = TTF_RenderText_Solid(font, "Bunny the ...", textColor);
                    nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
                    descriptionSurface = TTF_RenderText_Solid(font, "Write here about Bunny, maybe the story of how he has fallen in the hole? Something funny to make the game COOL", textColor);
                    descriptionTexture = SDL_CreateTextureFromSurface(renderer, descriptionSurface);
                } else if(sprite3 == true) {
                    sprite = sprite3StraightTexture;
                    nameSurface = TTF_RenderText_Solid(font, "Matthew the ...", textColor);
                    nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
                    descriptionSurface = TTF_RenderText_Solid(font, "Write here about Matthew, maybe the story of how he has fallen in the hole? Something funny to make the game COOL", textColor);
                    descriptionTexture = SDL_CreateTextureFromSurface(renderer, descriptionSurface);
                }

                SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect);
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect2);
                SDL_RenderCopy(renderer, sprite, NULL, &sprite_rect2);
                SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);
                SDL_RenderCopy(renderer, descriptionTexture, NULL, &descriptionRect);
                SDL_RenderCopy(renderer, infoTexture, NULL, &infoRect);

                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(nameTexture);
                SDL_DestroyTexture(descriptionTexture);
                SDL_DestroyTexture(infoTexture);
                SDL_FreeSurface(nameSurface);
                SDL_FreeSurface(descriptionSurface);
                SDL_FreeSurface(infoSurface);

            } else if (main_menu_screen == true) {
                counterAdd = 45;
                Title_rect.x = 150;
                Title_rect.y = 2;
                Title_rect.w = 700;
                Title_rect.h = 300;
                menuCounter += 2;
                fallCounter += 0.5;
                backCounter += 6;
                backCounter2 += 6;

                if(fallCounter >= 500){
                    fall = true;
                    fallCounter = 0;
                }

                if(starty == 530){
                    add = false;
                }else if(starty == 510){
                    add = true;
                }

                SDL_Rect falling_rect = {fallx, fally, 100, 100};
                SDL_Rect border_rect = {position, 325, 160, 160};

                SDL_Color textColor = {255, 255, 255};
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect);
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect2);
                SDL_RenderCopy(renderer, sprite1FallingTexture, NULL, &falling_rect);//copied here to appear behind text
                SDL_RenderCopy(renderer, sprite1StraightTexture, NULL, &sprite1_rect);
                SDL_RenderCopy(renderer, sprite2StraightTexture, NULL, &sprite2_rect);
                SDL_RenderCopy(renderer, sprite3StraightTexture, NULL, &sprite3_rect);
                SDL_RenderCopy(renderer, border, NULL, &border_rect);

                SDL_Surface* titleMessage = TTF_RenderText_Solid(font, "DUNGEON FALL", textColor);
                SDL_Texture* titleMessage2 = SDL_CreateTextureFromSurface(renderer, titleMessage);
                SDL_RenderCopy(renderer, titleMessage2, NULL, &Title_rect);

                SDL_Rect MainMenu_rect = {startx, starty, 400, 50};
                SDL_Rect pick_rect = {190, 265, 300, 40};

                if(add){
                    if(menuCounter == 4){
                        starty += 1;
                        menuCounter = 0;
                    }
                }else{
                    if(menuCounter == 4){
                        starty -= 1;
                        menuCounter = 0;
                    }
                }

                if(fall){
                    fally += 1;
                }

                if(position == 185) {
                    sprite1 = true;
                    sprite2 = false;
                    sprite3 = false;
                } else if (position == 385) {
                    sprite1= false;
                    sprite2 = true;
                    sprite3 = false;
                } else if(position == 585){
                    sprite1 = false;
                    sprite2 = false;
                    sprite3 = true;
                }

                SDL_Surface* mainMessage = TTF_RenderText_Solid(font, "Press space bar to start!", textColor);
                SDL_Texture* mainMessage2 = SDL_CreateTextureFromSurface(renderer, mainMessage);
                SDL_Surface* pickMessage = TTF_RenderText_Solid(font, "Select a character:", textColor);
                SDL_Texture* pickMessage2 = SDL_CreateTextureFromSurface(renderer, pickMessage);

                SDL_RenderCopy(renderer, pickMessage2, NULL, &pick_rect);
                SDL_RenderCopy(renderer, mainMessage2, NULL, &MainMenu_rect);

                SDL_RenderPresent(renderer);//present the title page

                SDL_DestroyTexture(pickMessage2);
                SDL_DestroyTexture(titleMessage2);//free resources
                SDL_DestroyTexture(mainMessage2);

                SDL_FreeSurface(pickMessage);
                SDL_FreeSurface(titleMessage);
                SDL_FreeSurface(mainMessage);
            }

            while(SDL_PollEvent(&event)){
                if(event.key.keysym.sym == SDLK_SPACE){
                    if(main_menu_screen == true) {
                        main_menu = false;
                        first_loop = true;
                    }
                }
                if(event.key.keysym.sym == SDLK_RETURN) {
                    main_menu_screen = false;
                    character_description = true;
                }
                if(event.key.keysym.sym == SDLK_BACKSPACE) {
                    character_description = false;
                    main_menu_screen = true;
                }
                if(event.key.keysym.sym == SDLK_RIGHT) {
                    if(position != 585) {
                        position += 100;
                    }
                }
                if(event.key.keysym.sym == SDLK_LEFT) {
                    if(position != 185) {
                        position -= 100;
                    }
                }
            }
        }else{
            if(game_over == true){

                Mix_PlayChannel( -1, keem, 0 );
                counterAdd = 45;

                SDL_Color textColor = {255, 255, 255};
                SDL_Rect game_over_back2 = {0, 0, 1000, 700};
                SDL_Rect GameOver_rect = {230, 50, 500, 100};
                SDL_Rect Attempts_rect = {380, 150, 200, 50};
                SDL_Rect Attempts_rect2 = {585, 150, 20, 45 };

                score = 0;

                move_left = false;
                move_right = false;
                move_up = false;
                move_down = false;

                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer, backTexture, NULL, &game_over_back2);

                SDL_Surface* gameOverSurface = TTF_RenderText_Solid(font, "Game Over!", textColor);
                SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);

                SDL_Surface* mainMessage = TTF_RenderText_Solid(font, "Press space bar to try again!", textColor);
                SDL_Texture* mainMessage2 = SDL_CreateTextureFromSurface(renderer, mainMessage);

                SDL_Surface* mainMessage3 = TTF_RenderText_Solid(font, "Press 'M' to return to the menu!", textColor);
                SDL_Texture* mainMessage4 = SDL_CreateTextureFromSurface(renderer, mainMessage3);

                SDL_Surface* attemptMessage = TTF_RenderText_Solid(font, "Attempt number: ", textColor);
                SDL_Texture* attemptMessage2 = SDL_CreateTextureFromSurface(renderer, attemptMessage);

                SDL_Surface* attemptCount = TTF_RenderText_Solid(font, array2, textColor);
                SDL_Texture* attemptCount2 = SDL_CreateTextureFromSurface(renderer, attemptCount);

                SDL_RenderCopy(renderer, gameOverTexture, NULL, &GameOver_rect);
                SDL_RenderCopy(renderer, attemptMessage2, NULL, &Attempts_rect);
                SDL_RenderCopy(renderer, attemptCount2, NULL, &Attempts_rect2);
                SDL_RenderCopy(renderer, mainMessage2, NULL, &MainMenu_rect);
                SDL_RenderCopy(renderer, mainMessage4, NULL, &MainMenu_rect2);

                SDL_RenderPresent(renderer);

                SDL_FreeSurface(gameOverSurface);
                SDL_DestroyTexture(gameOverTexture);
                SDL_FreeSurface(mainMessage);
                SDL_DestroyTexture(mainMessage2);
                SDL_FreeSurface(mainMessage3);
                SDL_DestroyTexture(mainMessage4);
                SDL_FreeSurface(attemptMessage);
                SDL_DestroyTexture(attemptMessage2);
                SDL_FreeSurface(attemptCount);
                SDL_DestroyTexture(attemptCount2);

                while(SDL_PollEvent(&event)){
                    if(event.key.keysym.sym == SDLK_SPACE){
                        game_over = false;
                        first_loop = true;
                    }
                    if(event.key.keysym.sym == SDLK_m){
                        game_over = false;
                        main_menu = true;
                    }
                }
                if(game_over == false){
                    x = 475;
                    y = 250;
                    oby = 600;
                    ob2y = 900;
                    mode = 0;
                    wallLeftX = -800;
                    wallRightX = 800;
                    wall_rect.x = wallLeftX;
                    wall_rect2.x = wallRightX;
                    wall_rect1_2.x = wallLeftX;
                    wall_rect2_2.x = wallRightX;
                }
            }else{
                SDL_Texture* spriteFallingTexture = NULL;
                if(sprite1 == true) {
                    spriteFallingTexture = sprite1FallingTexture;
                } else if (sprite2 == true) {
                    spriteFallingTexture = sprite2FallingTexture;
                } else if (sprite3 == true) {
                    spriteFallingTexture = sprite3FallingTexture;
                }

                SDL_RenderClear(renderer);
                float count = 0;
                fallx = 475;
                fally = -100;

                if(first_loop){
                    wall_rect.y = -600;
                    wall_rect2.y = -600;
                    wall_rect1_2.y = -600;
                    wall_rect2_2.y = -600;
                }

                while(first_loop){

                    SDL_Delay(time_left());
                    next_time += TICK_INTERVAL;

                    SDL_RenderClear(renderer);
                    count += 10;
                    counter3 += 60;
                    counter4 += 60;
                    counter2+= 60;
                    counter+= 60;

                    SDL_Color textColor = {255, 255, 255};

                    //if(counter >= 100){
                        counter = 0;
                        background_rect.y -= 3;
                    //}
                    if(background_rect.y <= -700){
                        background_rect.y = 700;
                    }

                    SDL_RenderCopy(renderer, backTexture, NULL, &background_rect);

                        counter2 = 0;
                        background_rect2.y -= 3;
                        Title_rect.y -= 3;

                    //}
                    if(background_rect2.y <= -700){
                        background_rect2.y = 700;
                    }

                    SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);

                    //if(counter3 > 50){
                        wall_rect.y -= 3;
                    //}
                    if(wall_rect.y <= -600){
                        wall_rect.y = 600;
                    }
                    SDL_RenderCopy(renderer, texture, NULL, &wall_rect);
                    //if(counter3 > 50){
                        wall_rect2.y -= 3;
                        counter3 = 0;
                   // }
                    if(wall_rect2.y <= -600){
                        wall_rect2.y = 600;
                    }
                    SDL_RenderCopy(renderer, texture, NULL, &wall_rect2);

                   //if(counter4 > 50){
                        wall_rect1_2.y -= 3;
                    //}
                    if(wall_rect1_2.y <= -1200){
                        wall_rect1_2.y = 600;
                    }
                    SDL_RenderCopy(renderer, texture, NULL, &wall_rect1_2);

                    //if(counter4 > 50){
                        counter4 = 0;
                        wall_rect2_2.y -= 3;
                    //}
                    if(wall_rect2_2.y <= -1200){
                        wall_rect2_2.y = 600;
                    }
                    SDL_RenderCopy(renderer, texture, NULL, &wall_rect2_2);
                    SDL_Surface* titleMessage = TTF_RenderText_Solid(font, "DUNGEON FALL", textColor);
                    SDL_Texture* titleMessage2 = SDL_CreateTextureFromSurface(renderer, titleMessage);
                    SDL_RenderCopy(renderer, titleMessage2, NULL, &Title_rect);

                    if(count > 1500){
                        SDL_Rect falling_rect = {fallx, fally, 80, 80};
                        SDL_RenderCopy(renderer, spriteFallingTexture, NULL, &falling_rect);
                        if(fally != 250){
                            fally += 2;
                        }
                        if(fally >= 250){
                            first_loop = false;
                            counter3 = 0.0;
                            counter4 = 0.0;
                        }
                    }
                    SDL_RenderPresent(renderer);
                    SDL_DestroyTexture(titleMessage2);
                    SDL_FreeSurface(titleMessage);

                }//animation ends here

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
                            rightmove = true;
                        }
                        if(event.key.keysym.sym == SDLK_LEFT){
                            move_left = true;
                            rightmove = false;
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

                counter += counterAdd;
                counter2 += counterAdd;
                counter3 += counterAdd;
                counter4 += counterAdd;
                if(score == 5000 || score == 10000 || score == 20000 || score == 30000 || score == 40000 || score == 50000){//speeds up falling pace
                    counterAdd += 5;
                }
                    if(x < wallLeftX + 1000 || x > wallRightX - 20){
                    x = 475;
                    y = 250;
                    game_over = true;
                }

                if(y > 550 || y < 0){
                    x = 475;
                    y = 250;
                    game_over = true;
                }

                if(counter >= 100){
                    background_rect.y -= 2;
                    counter = 0;
                }

                if(background_rect.y <= -700){
                    background_rect.y = 700;
                }

                SDL_RenderCopy(renderer, backTexture, NULL, &background_rect);

                if(counter2 >= 100){
                    counter2 = 0;
                    background_rect2.y -= 2;
                }
                if(background_rect2.y <= -700){
                    background_rect2.y = 700;
                }

                SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

                // Draw a rectangle
                SDL_Rect rect = {x, y, 80, 80};
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_RenderFillRect(renderer, &rect);



                if(rightmove){
                    float angle = 0.0; // set the angle.
                    SDL_Point center = {8, 8}; // the center where the texture will be rotated.
                    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL; // the flip of the texture.

                        // now, try to draw something
                    SDL_RenderCopyEx(renderer, spriteFallingTexture, NULL , &rect, angle, &center, flip);
                }else{
                    SDL_RenderCopy(renderer, spriteFallingTexture, NULL, &rect);
                }

                if(location > 550){
                    location = 200;
                }

                score++;
                sprintf(array, "%d", score);

                SDL_Color textColor = { 255, 255, 255 };

                surfaceMessage = TTF_RenderText_Solid(font2, array, textColor);
                surfaceMessage2 = TTF_RenderText_Solid(font, "Score: ", textColor);

                Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);

                SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
                SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);

                    // Show what was drawn
                if(counter3 > 50){
                    wall_rect.y -= 4;
                }
                if(wall_rect.y <= -600){
                    wall_rect.y = 600;
                }
                SDL_RenderCopy(renderer, texture, NULL, &wall_rect);

                if(counter3 > 50){
                    wall_rect2.y -= 4;
                    counter3 = 0;
                }
                if(wall_rect2.y <= -600){
                    wall_rect2.y = 600;
                }
                SDL_RenderCopy(renderer, texture, NULL, &wall_rect2);

                if(counter4 > 50){
                    wall_rect1_2.y -= 4;
                }
                if(wall_rect1_2.y <= -600){
                    wall_rect1_2.y = 600;
                }
                SDL_RenderCopy(renderer, texture, NULL, &wall_rect1_2);

                if(counter4 > 50){
                    counter4 = 0;
                    wall_rect2_2.y -= 4;
                }
                if(wall_rect2_2.y <= -600){
                    wall_rect2_2.y = 600;
                }

                SDL_RenderCopy(renderer, texture, NULL, &wall_rect2_2);

                if(score % 1000 == 0){
                    switchModes = true;
                }
                if(mode == 0){
                    oby -= speed;
                    ob2y -= speed;

                    if(!switchModes){
                        if(x + 20 >= obx && x <= obx + 70){
                            if(oby + 50 >= y && oby <= y+50){
                                game_over = true;
                            }
                        }
                        if(x + 20 >= ob2x && x <= ob2x + 50){
                            if(oby + 50 >= y && oby <= y+50){
                                game_over = true;
                            }
                        }

                        if(x + 20 >= ob3x && x <= ob3x + 100){
                            if(oby + 50 >= y && oby <= y+50){
                                game_over = true;
                            }
                        }

                        if(oby < -50){
                            obx = (rand() % 520)+200;
                            ob2x = (rand() % 550)+200;
                            ob3x = (rand() % 500)+200;
                            oby = 600;
                            counted1 = 0;
                        }

                        if(x + 20 >= ob4x && x <= ob4x + 70){
                            if(ob2y + 50 >= y && ob2y <= y+50){
                                game_over = true;
                            }
                        }
                        if(x + 20 >= ob5x && x <= ob5x + 50){
                            if(ob2y + 50 >= y && ob2y <= y+50){
                                game_over = true;
                            }
                        }

                        if(x + 20 >= ob6x && x <= ob6x + 100){
                            if(ob2y + 50 >= y && ob2y <= y+50){
                                game_over = true;
                            }
                        }

                        if(ob2y < -50){
                            ob4x = (rand() % 520)+200;
                            ob5x = (rand() % 550)+200;
                            ob6x = (rand() % 500)+200;
                            ob2y = 600;
                            counted2 = 0;
                            phases++;
                        }
                    } else {
                        if(oby <= -50 && ob2y <= -50){
                            mode = 1;
                            oby = 600;
                            ob2y = 900;
                            setup = true;
                            switchModes = false;
                        }
                    }

                    SDL_Rect rect2 = {obx, oby, 100, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireBlueTexture, NULL, &rect2);
                    SDL_Rect rect3 = {ob2x, oby, 70, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireGreenTexture, NULL, &rect3);
                    SDL_Rect rect4 = {ob3x, oby, 100, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireRedTexture, NULL, &rect4);
                    SDL_Rect rect5 = {ob4x, ob2y, 100, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireBlueTexture, NULL, &rect5);
                    SDL_Rect rect6 = {ob5x, ob2y, 70, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireGreenTexture, NULL, &rect6);
                    SDL_Rect rect7 = {ob6x, ob2y, 100, 50};
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_RenderCopy(renderer, fireRedTexture, NULL, &rect7);

                } else {
                    int speed2 = 2;
                    if(!switchModes){
                        if(setup){
                            wallLeftX += speed2;
                            wallRightX -= speed2;
                            wall_rect.x = wallLeftX;
                            wall_rect2.x = wallRightX;
                            wall_rect1_2.x = wallLeftX;
                            wall_rect2_2.x = wallRightX;

                            if(wallLeftX >= -625){
                                setup = false;
                                complete = false;
                                pos = rand() % 4;
                            }
                        } else {
                            wall_rect.x = wallLeftX;
                            wall_rect2.x = wallRightX;
                            wall_rect1_2.x = wallLeftX;
                            wall_rect2_2.x = wallRightX;

                            if(pos == 0){
                                if(!complete){

                                    wallLeftX -= speed2;
                                    wallRightX -= speed2;

                                    if(wallLeftX <= wallPos1-1000){
                                        pos = rand() % 4;
                                    }
                                }
                            } else if(pos == 1){
                                if(!complete){
                                    if(wallLeftX < wallPos2 - 1000) {
                                        wallLeftX += speed2;
                                        wallRightX += speed2;
                                        if(wallLeftX >= wallPos2-1000){
                                            pos = rand() % 4;
                                        }
                                    } else {
                                        wallLeftX -= speed2;
                                        wallRightX -= speed2;
                                        if(wallLeftX <= wallPos2-1000){
                                            pos = rand() % 4;
                                        }
                                    }
                                }
                            } else if(pos == 2){
                                if(!complete){
                                    if(wallLeftX < wallPos3 - 1000) {
                                        wallLeftX += speed2;
                                        wallRightX += speed2;
                                        if(wallLeftX >= wallPos3-1000){
                                            pos = rand() % 4;
                                        }
                                    } else {
                                        wallLeftX -= speed2;
                                        wallRightX -= speed2;
                                        if(wallLeftX <= wallPos3-1000){
                                            pos = rand() % 4;
                                        }
                                    }
                                }
                            } else {
                                if(!complete){
                                    wallLeftX += speed2;
                                    wallRightX += speed2;
                                        if(wallLeftX >= wallPos4-1000){
                                        //complete = true;
                                        pos = rand() % 4;
                                    }
                                }
                            }
                        }

                        if(score % 1000 == 0){
                            switchModes = true;
                        }

                    } else {
                        if(wallLeftX > -800){
                            wallLeftX -= speed2;
                        } else if (wallLeftX < -800){
                            wallLeftX += speed2;
                        }
                        if(wallRightX < 800){
                            wallRightX += speed2;
                        } else if(wallRightX < 800){
                            wallRightX += speed2;
                        }
                        if(wallLeftX <= -800 && wallRightX >= 800){
                            wallLeftX = -800;
                            wallRightX = 800;
                            mode = 0;
                            switchModes = false;
                        }
                        wall_rect.x = wallLeftX;
                        wall_rect2.x = wallRightX;
                        wall_rect1_2.x = wallLeftX;
                        wall_rect2_2.x = wallRightX;
                    }
                }
                if(game_over){
                    attempts++;
                    sprintf(array2, "%d", attempts);
                }
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(Message);
                SDL_DestroyTexture(Message2);
                SDL_FreeSurface(surfaceMessage);
                SDL_FreeSurface(surfaceMessage2);
            }
        }
    }

    free(array);

    TTF_CloseFont(font);//releases font resource

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //SDL Quits
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
