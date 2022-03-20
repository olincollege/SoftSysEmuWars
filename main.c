#include <stdio.h>
#include "chip-8.h"
#include "opcodes.h"
#include "graphics.h"

int main(int argc, char const *argv[])
{
    if (argc != 2) {
		fprintf(stderr, "Please provide a filename");
		exit(1);
	}

    // perform setup 
    memset(display, 0, sizeof(display));    // Clear display
    memset(stack, 0, sizeof(stack));        // Clear stack
    memset(V, 0, sizeof(V));                // Clear registers V0-VF
    memset(memory, 0, sizeof(memory));      // Clear memory
    load_font();

    char const* file_name = argv[1];
    uint8_t *loc_display = display;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize the CPU to starting values
    //init_cpu();
    //initialize the graphics
    init_graphics(&window, &renderer, &texture, SCREEN_WIDTH * SCALE, \
    SCREEN_HEIGHT * SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);
    // load the game into memory
    load_game(file_name);

    int quit = 0;
    while (!quit) {
        quit = process_input(keys);
        // fetch the next opcode and increment the program counter
        opcode = (memory[PC] << 8) | memory [PC + 1];
        PC += 2;

        // decode and execute
        switch (opcode & 0xF000) {
            case 0x0000:
                switch (opcode){
                case 0x00E0:
                    op_00E0();
                    break;
                case 0x00EE:
                    op_00EE();
                    break;
                default:
                    fprintf(stderr, "Unknown opcode: %x", opcode);
                    break;
                }
                break;
            case 0x1000:
                op_1nnn();
                break;
            case 0x2000:
                op_2nnn();
                break;
            case 0x6000:
                op_6xnn();
                break;
            case 0x7000:
                op_7xnn();
                break;
            case 0xA000:
                op_Annn();
                break;
            case 0xD000:
                op_Dxyn();
                break;
            default: 
                fprintf(stderr, "Unknown opcode: %x", opcode);
        }   
        // update the timers
        if (delay_timer > 0)
        {
            --delay_timer;
        }

        if (sound_timer > 0)
        {
            --sound_timer;
        }

        update_graphics(&renderer, &texture, &loc_display, ROW_SIZE);
    }
    quit_graphics(window, renderer, texture);
}
