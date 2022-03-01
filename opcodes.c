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


