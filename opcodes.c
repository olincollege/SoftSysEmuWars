#include <stdio.h>
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

