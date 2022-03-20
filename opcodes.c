#include "opcodes.h"

// Clear the display
void op_00E0() {
    memset(display, 0, sizeof(display));
}

// Return from a subroutine
// Essentially go back down the stack 
void op_00EE() {
    --stack_pointer;
    PC = stack[stack_pointer];
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
    stack[stack_pointer] = PC;
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
    I = address;
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
    uint8_t height = opcode & 0x000F;

    // get the x and y positions from the registers 
    // wrap if the coordinates are bigger than the display width/height
    uint8_t x_pos = V[Vx] % SCREEN_WIDTH;
    uint8_t y_pos = V[Vy] % SCREEN_HEIGHT;
    
    // set the collision flag to 0
    V[0xF] = 0;

    // iterate over all the sprite rows
    for (int row = 0; row < height; row++) {
        uint8_t spriteByte = memory[I + row];
        // iterate over each column, there are guarunteed to be 8. 
        // we are working with a single pixel now 
        // printf("Sprite Byte: %" PRIu8 "\n", spriteByte);
        for (int col = 0; col < 8; col++) {
            // get the next pixel in the sprite
            uint8_t spritePixel = (spriteByte >> (7 - col)) & 0x1;
            // make a pointer to the corresponding pixel in the display
            // we do this because we will want to modify the pixel directly
            uint8_t * displayPixel = &display[(y_pos + row) * SCREEN_WIDTH + (x_pos + col)];
            // printf("Sprite Pixel: %" PRIu8 "\n", spritePixel);

            if (spritePixel) {
                // check if this would cause a collision
                if (spritePixel & *displayPixel) {
                    V[0xF] = 1;
                }

                // set the new pixel value in the display
                *displayPixel = *displayPixel ^ 0xFF;
                printf("Sprite Pixel: %" PRIu8 "\n", spritePixel);
            } else {
                // TODO: not sure if this line is necessary, revisit later
                *displayPixel = *displayPixel ^ 0;
            }

        }
    }
}
