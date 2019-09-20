int option = 0;
SDL_Rect mainMenuRect = {345, 340, 300, 260};
SDL_Rect blueArrowRect = {300, 340, 50, 50};


SDL_Surface *mainMenuOptions = IMG_Load("content/mainMenu.png");
SDL_Texture *mainMenuOptionsTexture = SDL_CreateTextureFromSurface(renderer, mainMenuOptions);
SDL_Surface *blueArrowSurface = IMG_Load("content/blueArrow.png");
SDL_Texture *blueArrowTexture = SDL_CreateTextureFromSurface(renderer, blueArrowSurface);

bool main_menu_test = true; //main_menu_screen needs to be false
else if (main_menu_test == true){
                if(option == 0){
                    blueArrowRect.y = 340;
                } else if(option == 1){
                    blueArrowRect.y = 400;
                } else if(option == 2){
                    blueArrowRect.y = 460;
                } else if(option == 3){
                    blueArrowRect.y = 520;
                }
                Title_rect.x = 150;
                Title_rect.y = 2;
                Title_rect.w = 700;
                Title_rect.h = 300;
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, backTexture, NULL, &background_rect2);//copys created stuff to the renderer
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect);
                SDL_RenderCopy(renderer, backTexture, NULL, &Title_background_rect2);
                SDL_RenderCopy(renderer, mainMenuOptionsTexture, NULL, &mainMenuRect);
                SDL_RenderCopy(renderer, mainMenuTitleTexture, NULL, &Title_rect);
                SDL_RenderCopy(renderer, blueArrowTexture, NULL, &blueArrowRect);
                SDL_RenderPresent(renderer);//draws the menu
            }
if(main_menu_test == true){

                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_SPACE){//start game
                        if(option == 0){
                            main_menu_test = false;
                            main_menu_screen = true;

                        }
                    }

                    if(event.key.keysym.sym == SDLK_UP) {
                        option--;
                        if(option == -1){
                            option = 3;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_DOWN) {
                        option++;
                        if(option == 4){
                            option = 0;
                        }
                    }
                }
                }
            } else {
                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_KEYDOWN){
                    if(event.key.keysym.sym == SDLK_SPACE){//start game
                        main_menu = false;
                        first_loop = true;
                    }
                    if(event.key.keysym.sym == SDLK_RETURN) {//look at current character
                        main_menu_screen = false;
                        character_description = true;
                    }
                    if(event.key.keysym.sym == SDLK_BACKSPACE) {//return from current character
                        character_description = false;
                        main_menu_screen = true;
                    }
                    if(event.key.keysym.sym == SDLK_RIGHT) {//move between characters
                        if(position != 585) {
                            position += 100;
                        }
                    }
                    if(event.key.keysym.sym == SDLK_LEFT) {//move between characters
                        if(position != 185) {
                            position -= 100;
                        }
                    }
                }
                }
            }
