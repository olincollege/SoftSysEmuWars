#include <stdio.h>
#include <stdint.h>
#include "chip-8.h"

// Clear the display
void op_00E0() {
    memset(display, 0, sizeof(display));
}

// Return from a subroutine
// Essentially go back down the stack 
void op_00EE() {
    --stack_pointer;
    PC = chip.stack[chip8.stack_pointer];
}

// Jump to location nnn in memory
void op_1nnn() {
    // Mask to grab only the last three bytes of the opcode
    // then set the program counter to that address 
    PC = opcode & 0x0FFF;
}

// Call subroutine at nnn
void op_2nnn() {
    //store where we are
    stack[stack_pointer] = pc;
    // now increment the stack pointer 
    ++stack_pointer;
    // and now jump to the new address
    PC = opcode & 0x0FFF;
}

// Set regeister Vx to nn
void op_6xnn() {
    // mask to find a) the register and b) what to set it to
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t byte = opcode & 0x00FF;

    // set the given register
    V[reg] = byte;
}

// Add value nn to register Vx
void op_7xnn() {
    // mask to find a) the register and b) what to set it to
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t byte = opcode & 0x00FF;

    // set the given register
    V[reg] += byte;
}

// Set the index register I to nnn
void op_Annn() {
    uint16_t address = opcode & 0x0FFF;
    I = address
}

/* 
Display a sprite of n bytes at Vx, Vy. Also set the VF collision flag. 

Drawing this display involves XORing the new sprite with the current display. 
So, if a pixel is 0 and is still 0, it stays 0, if it was 0 and is now 1, it
becomes 1, if it is 1 and now 0 it becomes 0. If it was 1 and is now 1 again,
it becomes 0 and we set the collision flag. 

Sprites wrap around in the sense that a y coordinate of 35 would wrap to
a y coordinate of 3, but do not wrap in the sense of a drawing being cut off
on one side of the screen and reappearing on the other.
*/
void op_Dxyn() {
    // get the x and y register addresses
    uint8_t Vx = (opcode & 0x0F00) >> 8;
    uint8_t Vy = (opcode & 0x00F0) >> 4;

    // get the x and y positions from the registers 
    // wrap if the coordinates are bigger than the display width/height
    uint8_t xPos = registers[Vx] % 64;
    uint8_t yPos = registers[Vy] % 32;
    
    // set the collision flag to 0
    registers[0xF] = 0;

    // TODO: iterate over the sprite pixels, find collisions, XOR 
}
