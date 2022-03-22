#include "graphics.h"

void init_graphics(SDL_Window **window_pointer, SDL_Renderer **renderer_pointer,\
    SDL_Texture **texture_pointer, int windowWidth, int windowHeight, \
    int textureWidth, int textureHeight) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            SDL_Quit();
            exit(1);
        }
    // create window and renderer at the same time 
    // use the window_shown flag so we can query window info later
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight,\
            SDL_WINDOW_SHOWN, window_pointer, renderer_pointer) != 0) 
    {
        SDL_Log("Unable to create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // create the texture 
    *texture_pointer = SDL_CreateTexture(*renderer_pointer, SDL_PIXELFORMAT_RGB332, \
            SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight); 
}

void update_graphics(SDL_Renderer **renderer, SDL_Texture **texture,\
    uint8_t **screen, int rowSize) {
    SDL_UpdateTexture(*texture, NULL, *screen, rowSize);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, *texture, NULL, NULL);
    SDL_RenderPresent(*renderer);
}

void quit_graphics(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int process_input(uint8_t *keys) {
    int quit = 0;

    SDL_Event event;
    
    // handle all keypresses in the queue
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: 
                quit = 1;
                break;
            case SDL_KEYDOWN:
                // get the code for the key that was pressed and
                // store the state it in the appropriate register
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                    case SDLK_x:
                        keys[0] = 1;
                        break;
                    case SDLK_1:
                        keys[1] = 1;
                        break;
                    case SDLK_2:
                        keys[2] = 1;
                        break;
                    case SDLK_3:
                        keys[3] = 1;
                        break;
                    case SDLK_q:
                        keys[4] = 1;
                        break;
                    case SDLK_w:
                        keys[5] = 1;
                        break;
                    case SDLK_e:
                        keys[6] = 1;
                        break;
                    case SDLK_a:
                        keys[7] = 1;
                        break;
                    case SDLK_s:
                        keys[8] = 1;
                        break;
                    case SDLK_d:
                        keys[9] = 1;
                        break;
                    case SDLK_z:
                        keys[0xA] = 1;
                        break;
                    case SDLK_c:
                        keys[0xB] = 1;
                        break;
                    case SDLK_4:
                        keys[0xC] = 1;
                        break;
                    case SDLK_r:
                        keys[0xD] = 1;
                        break;
                    case SDLK_f:
                        keys[0xE] = 1;
                        break;
                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
            } break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_x:
                        keys[0] = 0;
                        break;
                    case SDLK_1:
                        keys[1] = 0;
                        break;
                    case SDLK_2:
                        keys[2] = 0;
                        break;
                    case SDLK_3:
                        keys[3] = 0;
                        break;
                    case SDLK_q:
                        keys[4] = 0;
                        break;
                    case SDLK_w:
                        keys[5] = 0;
                        break;
                    case SDLK_e:
                        keys[6] = 0;
                        break;
                    case SDLK_a:
                        keys[7] = 0;
                        break;
                    case SDLK_s:
                        keys[8] = 0;
                        break;
                    case SDLK_d:
                        keys[9] = 0;
                        break;
                    case SDLK_z:
                        keys[0xA] = 0;
                        break;
                    case SDLK_c:
                        keys[0xB] = 0;
                        break;
                    case SDLK_4:
                        keys[0xC] = 0;
                        break;
                    case SDLK_r:
                        keys[0xD] = 0;
                        break;
                    case SDLK_f:
                        keys[0xE] = 0;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0;
                        break;
            } break;
        }
    } 
    
    return quit;
}





