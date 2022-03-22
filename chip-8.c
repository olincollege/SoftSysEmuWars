#include "chip-8.h"

// define the external variables here
uint16_t PC = START_ADDRESS; 
uint16_t opcode = 0;
uint16_t I = 0;
uint16_t stack_pointer = 0;

uint8_t memory[MEMORY_SIZE]; 
uint8_t display[SCREEN_WIDTH*SCREEN_HEIGHT];
uint16_t stack[16];
uint8_t keys[16];
uint8_t V[16];

uint8_t delay_timer = 0;
uint8_t sound_timer = 0;

unsigned char chip8_fontset[80] =
    { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void load_font() {
    for(int i = 0; i < 80; ++i) {
        memory[FONTSET_START_ADDRESS + i] = chip8_fontset[i];
    }	
}


void init_cpu() {
    memset(display, 0, sizeof(display));    // Clear display
    memset(stack, 0, sizeof(stack));        // Clear stack
    memset(V, 0, sizeof(V));                // Clear registers V0-VF
    memset(memory, 0, sizeof(memory));      // Clear memory

    load_font();
}


void load_game(const char *filename) {
    FILE *game;

    // Read the binary game file
    game = fopen(filename, "rb");

    if (NULL == game) {
        fprintf(stderr, "Unable to open game: %s\n", filename);
        exit(1);
    }
    // Read the game data into memory starting at address 0x200
    fread(&memory[0x200], 1, MAX_GAME_SIZE, game);

    fclose(game);
}