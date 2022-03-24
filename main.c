#include <sys/time.h>
#include <time.h>
#include "chip-8.h"
#include "opcodes.h"
#include "graphics.h"

struct timeval prev_time;

// find second difference and microsecond difference to find total
int64_t find_dt(struct timeval *end_time, struct timeval *start_time) {
    // multiplying by 1000 converts seconds to milliseconds
    // dividing by 1000 converts microseconds to milliseconds
    int64_t time_diff_milli = (end_time->tv_sec - start_time->tv_sec) * 1000 + 
        (end_time->tv_usec - start_time->tv_usec) / 1000;
    return time_diff_milli;
}


/*
One cycle of the CHIP-8 fetches an opcode, then decodes it
and executes whatever it says to do. 

Opcodes: opcodes are two bytes but are stored in memory as
a single byte. This means we have to fetch two successive bytes from memory 
to get the next opcode. The program counter points to our location in memory. 
Every time we fetch a new opcode we must increment it by two. 

Fetching: First we fetch the byte where the program counter is pointing. 
We shift it over by a byte (so if the opcode was 11111111 we would have 
1111111100000000) and fetch the next byte from memory. We can combine these by 
using the OR bitwise operation to obtain an entire opcode. We then need to
increase the program counter by two, since fetching one opcode moved us 
two bytes along in memory. 

Note that we need to remember that we have incremented the PC BEFORE decoding
or executing the opcodes, since opcodes themselves can increment or decrement
the PC. 
*/
int main(int argc, char const *argv[])
{
    if (argc != 3) {
		fprintf(stderr, "Please provide a filename");
		exit(1);
	}

    char const* file_name = argv[1];
    int cycle_time = atoi(argv[2]);

    // setup random number generator
    srand(time(NULL));

    uint8_t *loc_display = display;

    // set up graphics structures
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize CPU arrays to starting values
    init_cpu();
    //initialize the graphics
    init_graphics(&window, &renderer, &texture, SCREEN_WIDTH * SCALE, \
    SCREEN_HEIGHT * SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);
    // load the game into memory
    load_game(file_name);

    int quit = 0;
    while (!quit) {
        quit = process_input(keys);
        struct timeval current_time;
        gettimeofday(&current_time, NULL);

        int64_t elapsed_time = find_dt(&current_time, &prev_time);
        // printf("Elapsed time: %ld\n", elapsed_time);

        if (elapsed_time >= cycle_time) {
            prev_time = current_time;

            // fetch the next opcode and increment the program counter
            opcode = (memory[PC] << 8) | memory [PC + 1];
            printf("Opcode: %x\n", opcode);
            PC += 2;

            // decode and execute
            switch (opcode & 0xF000) {
                case 0x0000:
                    switch (opcode & 0xFF){
                    case 0x00E0:
                        op_00E0();
                        break;
                    case 0x00EE:
                        op_00EE();
                        break;
                    default:
                        fprintf(stderr, "Unknown opcode: %x\n", opcode);
                        //exit(1);
                    } break;
                case 0x1000:
                    op_1nnn();
                    break;
                case 0x2000:
                    op_2nnn();
                    break;
                case 0x3000:
                    op_3xnn();
                    break;
                case 0x4000:
                    op_4xnn();
                    break;
                case 0x5000:
                    op_5xy0();
                    break;
                case 0x6000:
                    op_6xnn();
                    break;
                case 0x7000:
                    op_7xnn();
                    break;
                case 0x8000:
                    switch (opcode & 0xF) {
                    case 0:
                        op_8xy0();
                        break;
                    case 1:
                        op_8xy1();
                        break;
                    case 2:
                        op_8xy2();
                        break;
                    case 3:
                        op_8xy3();
                        break;
                    case 4:
                        op_8xy4();
                        break;
                    case 5:
                        op_8xy5();
                        break;
                    case 6:
                        op_8xy6();
                        break;
                    case 7:
                        op_8xy7();
                        break;
                    case 0xE:
                        op_8xyE();
                        break;
                    default:
                        fprintf(stderr, "Unknown opcode: %x\n", opcode);
                        //exit(1);
                    } break;
                case 0x9000:
                    op_9xy0();
                    break;
                case 0xA000:
                    op_Annn();
                    break;
                case 0xB000:
                    op_Bnnn();
                    break;
                case 0xC000:
                    op_Cxnn;
                    break;
                case 0xD000:
                    op_Dxyn();
                    break;
                case 0xE000:
                    switch (opcode & 0x00FF) {
                        case 0x009E:
                            op_Ex9E();
                            break;
                        case 0x00A1:
                            op_ExA1();
                            break;
                        default:
                            fprintf(stderr, "Unknown opcode: %x\n", opcode);
                            //exit(1);
                    } break;
                case 0xF000:
                    switch (opcode & 0x00FF) {
                        case 0x0007:
                            op_Fx07();
                            break;
                        case 0x000A:
                            op_Fx0A();
                            break;
                        case 0x0015:
                            op_Fx15();
                            break;
                        case 0x0018:
                            op_Fx18();
                            break;
                        case 0x001E:
                            op_Fx1E();
                            break;
                        case 0x0029:
                            op_Fx29();
                            break;
                        case 0x0033:
                            op_Fx33();
                            break;
                        case 0x0055:
                            op_Fx55();
                            break;
                        case 0x0065:
                            op_Fx65();
                            break;
                        default:
                            printf("running default in the F switch statement");
                            fprintf(stderr, "Unknown opcode: %x\n", opcode);
                            //exit(1);
                    } break;
                default: 
                    fprintf(stderr, "Unknown opcode: %x\n", opcode);
                    //exit(1);
            }   
            // update the timers
            if (delay_timer > 0) {
                --delay_timer;
            }

            if (sound_timer > 0) {
                --sound_timer;
            }

            update_graphics(&renderer, &texture, &loc_display, ROW_SIZE);
            
        }
    }
    quit_graphics(window, renderer, texture);
}
