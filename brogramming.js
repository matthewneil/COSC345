 float fireObjectsX[] = {(rand() % 480)+200, (rand() % 480)+200, (rand() % 480)+200,
                            (rand() % 480)+200, (rand() % 480)+200, (rand() % 480)+200};
                            
                      for(int i=0; i<6; i++){
                            if(x + 20 >= fireObjectsX[i] && x <= fireObjectsX[i] + 100) {//collision detection for fireballs
                                if(i < 3){
                                    if(oby + 50 >= y && oby <= y + 50) {
                                        game_over = true;
                                    }
                                } else {
                                    if(ob2y + 50 >= y && ob2y <= y + 50) {
                                        game_over = true;
                                    }
                                }
                            }
                        }
                        if(oby < -78) {//resets the objects to be used again once off screen
                            while(true){
                                fireObjectsX[0] = (rand() % 480) + 200;
                                fireObjectsX[1] = (rand() % 480) + 200;
                                fireObjectsX[2] = (rand() % 480) + 200;
                                oby = 700;
                                if(fireObjectsX[0] - fireObjectsX[1] > 120 || fireObjectsX[1] - fireObjectsX[0] > 120){
                                    if(fireObjectsX[0] - fireObjectsX[2] > 120 || fireObjectsX[2] - fireObjectsX[0] > 120) {
                                        if(fireObjectsX[1] - fireObjectsX[2] > 120 || fireObjectsX[2] - fireObjectsX[1] > 120) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }

                        if(ob2y < -78 || (first_time && oby <= 350)) {//resets the objects to be used again once off screen
                            first_time = false;
                            while(true){
                                fireObjectsX[3] = (rand() % 480) + 200;
                                fireObjectsX[4] = (rand() % 480) + 200;
                                fireObjectsX[5] = (rand() % 480) + 200;
                                ob2y = 700;
                                if(fireObjectsX[3] - fireObjectsX[4] > 120 || fireObjectsX[4] - fireObjectsX[3] > 120){
                                    if(fireObjectsX[3] - fireObjectsX[5] > 120 || fireObjectsX[5] - fireObjectsX[3] > 120) {
                                        if(fireObjectsX[4] - fireObjectsX[5] > 120 || fireObjectsX[5] - fireObjectsX[4] > 120) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        SDL_Rect rect_blue_1 = {fireObjectsX[0], oby, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_1);
                    SDL_Rect rect_blue_2 = {fireObjectsX[0]+30, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_2);
                    SDL_Rect rect_blue_3 = {fireObjectsX[0]+60, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_3);
                    SDL_Rect rect_blue_4 = {fireObjectsX[0]+90, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_4);
                    SDL_Rect rect_blue_5 = {fireObjectsX[3], ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_5);
                    SDL_Rect rect_blue_6 = {fireObjectsX[3]+30, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_6);
                    SDL_Rect rect_blue_7 = {fireObjectsX[3]+60, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_7);
                    SDL_Rect rect_blue_8 = {fireObjectsX[3]+90, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireBlueTexture, &source_rect_blue, &rect_blue_8);

                    SDL_Rect rect_green_1 = {fireObjectsX[1], oby, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_1);
                    SDL_Rect rect_green_2 = {fireObjectsX[1]+30, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_2);
                    SDL_Rect rect_green_3 = {fireObjectsX[1]+60, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_3);
                    SDL_Rect rect_green_4 = {fireObjectsX[1]+90, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_4);
                    SDL_Rect rect_green_5 = {fireObjectsX[4], ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_5);
                    SDL_Rect rect_green_6 = {fireObjectsX[4]+30, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_6);
                    SDL_Rect rect_green_7 = {fireObjectsX[4]+60, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_7);
                    SDL_Rect rect_green_8 = {fireObjectsX[4]+90, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireGreenTexture, &source_rect_green, &rect_green_8);

                    SDL_Rect rect_red_1 = {fireObjectsX[2], oby, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_1);
                    SDL_Rect rect_red_2 = {fireObjectsX[2]+30, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_2);
                    SDL_Rect rect_red_3 = {fireObjectsX[2]+60, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_3);
                    SDL_Rect rect_red_4 = {fireObjectsX[2]+90, oby, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_4);
                    SDL_Rect rect_red_5 = {fireObjectsX[5], ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_5);
                    SDL_Rect rect_red_6 = {fireObjectsX[5]+30, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_6);
                    SDL_Rect rect_red_7 = {fireObjectsX[5]+60, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_7);
                    SDL_Rect rect_red_8 = {fireObjectsX[5]+90, ob2y, 30, 78};
                    SDL_RenderCopy(renderer, fireRedTexture, &source_rect_red, &rect_red_8);
