#include <stdio.h>
#include <string.h>
#include "chip-8.h"

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

void init() {
    struct chip8_cpu chip8;
    
    PC = START_ADDRESS; // this is where the system expects the app to be loaded
    opcode = 0;
    I = 0;
    stack_pointer = 0;

    memset(display, 0, sizeof(display));    // Clear display
    memset(stack, 0, sizeof(stack));        // Clear stack
    memset(V, 0, sizeof(V));                // Clear registers V0-VF
    memset(memory, 0, sizeof(memory));      // Clear memory

    load_font();
}

void load_game(char *filename) {
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

/*
Represents one cycle of the CHIP-8. It fetches an opcode, then decodes it
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

void run_cycle() {
    // fetch the next opcode
    opcode = (memory[PC] << 8) | memory [PC + 1];
    // increment the program counter
    PC += 2;

    switch (opcode & 0xF000) {
        case default: 
            fprintf(stderr, "Unknown opcode: %i", opcode);
    }

}