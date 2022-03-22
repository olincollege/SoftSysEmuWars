#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_ADDRESS 0x200
#define FONTSET_START_ADDRESS 0x50
#define MEMORY_SIZE 0x1000  // 4096 in hex
#define MAX_GAME_SIZE (MEMORY_SIZE - START_ADDRESS)
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define SCALE 10


extern uint16_t opcode; // shorts are two bytes, so are opcodes
extern uint8_t memory[MEMORY_SIZE]; 

#define ROW_SIZE sizeof(memory[0]) * SCREEN_WIDTH

extern uint8_t V[16]; // CPU registers use chars because a char is 1 byte/8 bits

extern uint16_t I; // index register
extern uint16_t PC; // program counter

extern uint8_t display[SCREEN_WIDTH*SCREEN_HEIGHT]; // store the state of each pixel;

extern uint8_t delay_timer;
extern uint8_t sound_timer;

extern uint16_t stack[16];
extern uint16_t stack_pointer; 

extern uint8_t keys[16]; // store the states of the keys

void load_font();
void init_cpu();
void load_game(const char *filename);
int keymap(unsigned char k);