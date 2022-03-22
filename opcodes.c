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

// Skip one instruction if Vx = nn
void op_3xnn() {
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t byte = opcode & 0x00FF;

    if (V[reg] == byte) {
        PC += 2;
    }
}

// Skip one instruction if Vx is not nn
void op_4xnn() {
    uint8_t reg = (opcode & 0x0F00) >> 8;
    uint8_t byte = opcode & 0x00FF;

    if (V[reg] != byte) {
        PC += 2;
    }
}

// Skip one instruction if the values in Vx and Vy are equal
void op_5xy0() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    if (V[x] == V[y]) {
        PC += 2;
    }
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

// Set the value of Vx to the value of Vy
void op_8xy0() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    V[x] = V[y];
}

// Set Vx to the bitwise OR of Vx and Vy
void op_8xy1() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    V[x] = V[x] | V[y];
}

// Set Vx to the bitwise AND of Vx and Vy
void op_8xy2() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    V[x] = V[x] & V[y];
}

// Set Vx to the bitwise XOR of Vx and Vy
void op_8xy3() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    V[x] = V[x] ^ V[y];
}

// Set Vx to Vx + Vy. If the result is greater than 255, set carry flag to 1
void op_8xy4() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    uint16_t sum = V[x] + V[y];

    if (V[x] > 255) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }

    V[x] = sum & 0xFF;
}

// Set Vx to Vx - Vy. If Vx is larger than Vy, set carry flag to 1
void op_8xy5() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    if (x > y) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }

    V[x] = V[x] - V[y];
}

// Shift the value in Vx 1 bit to the right. Set carry to flag to the bit
// that was shifted out
void op_8xy6() {
    uint8_t x = (opcode & 0x0F00) >> 8;

    // the shifted out bit will be the last bit, mask to find it
    V[0xF] = V[x] & 0x1;
    // now shift 
    V[x] = V[x] >> 1;
}

// Set Vx to Vy - Vx. If Vy is larger than Vx, set carry flag to 1
void op_8xy7() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    if (y > x) {
        V[0xF] = 1;
    } else {
        V[0xF] = 0;
    }

    V[x] = V[y] - V[x];
}

// Shift the value in Vx 1 bit to the left. Set carry to flag to the bit
// that was shifted out
void op_8xyE() {
    uint8_t x = (opcode & 0x0F00) >> 8;

    // the shifted out bit will be the first bit of the byte, mask to find it 
    // then shift it over so it's a single bit in the ones place
    V[0xF] = (V[x] & 0x80) >> 7;
    // now left-shift Vx
    V[x] = V[x] << 1;
}

// Skip the next instruction if Vx and Vy are not equal
void op_9xy0() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x0F00) >> 4;

    if (V[x] != V[y]) {
        PC += 2;
    }
}

// Set the index register I to nnn
void op_Annn() {
    uint16_t address = opcode & 0x0FFF;
    I = address;
}

// Jump to location nnn + V0
void op_Bnnn() {
    uint16_t address = opcode & 0x0FFF;
    PC = V[0] + address;
}

// Generate a random number, set Vx to the random number & nn
void op_Cxnn() {
    // generate a random number between 0 and 255
    uint8_t rand_num = rand() % 256;
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t nn = opcode & 0x00FF;
    V[x] = nn; 
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
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    uint8_t height = opcode & 0x000F;

    // get the x and y positions from the registers 
    // wrap if the coordinates are bigger than the display width/height
    uint8_t x_pos = V[x] % SCREEN_WIDTH;
    uint8_t y_pos = V[y] % SCREEN_HEIGHT;
    
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
                // printf("Sprite Pixel: %" PRIu8 "\n", spritePixel);
            } else {
                // TODO: not sure if this line is necessary, revisit later
                *displayPixel = *displayPixel ^ 0;
            }
        }
    }
}

// Skip the next instruction if the key in Vx is pressed
void op_Ex9E() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t key = V[x];

    if (keys[key] == 1) {
        PC += 2;
    }
}

// Skip the next instruction if the key in Vx is NOT pressed
// Skip the next instruction if the key in Vx is pressed
void op_ExA1() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t key = V[x];

    if (keys[key] == 0) {
        PC += 2;
    }
}

// Set Vx to the current value of the delay timer
void op_Fx07() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    V[x] = delay_timer;
}

// Stop execution until a key is pressed. When it is, store the value in Vx
void op_Fx0A() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    int key_press_found = 0;
    while (!key_press_found) {
        for (int i = 0; i < 16; i++) {
            if (keys[i]) {
                V[x] = i;
                key_press_found = 1;
            }
            if (key_press_found) {
                break;
            } else {
                // Decrement the PC if no keypress to stop it from going to
                // the next instruction
                PC -= 2;
            }
        }
    }
}


// Set the delay timer to the value of Vx
void op_Fx15() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    delay_timer = V[x];
}

// Set the sound timer to the value of Vx
void op_Fx18() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    sound_timer = V[x];
}

// Add the value in Vx to I
void op_Fx1E() {
    uint8_t x = (opcode & 0x0F00) >> 8;

    I += V[x];
}

// Set I to the memory address of the font character in Vx
void op_Fx29() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t fetch_char = V[x];

    // Start from where the font starts in memory. We know font characters
    // are 5 bytes long, so we can find the right location 
    I = FONTSET_START_ADDRESS + (5 * fetch_char);
}

// Take the number in Vx (between 0 and 255) and put the first digit at memory
// address I, the second at I + 1, and the last at I + 2. If Vx was 255, 
// we would store 2 at I, 5 at I + 1, and 5 at I + 2
void op_Fx33() {
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t value = V[x];

    // ones place is the remainder
    memory[I + 2] = value % 10;
    // This is essentially floor division since value is an int
    value = value / 10;

    // tens place
    memory[I + 1] = value % 10;
    value = value / 10;

    // hundreds place
    memory[I] = value % 10;
}

// Store register V[0] through V[x] in memory starting at location I
void op_Fx55() {
    uint8_t x = (opcode & 0x0F00) >> 8;

    for (int j=0; j <= x; j++) {
        memory[I + j] = V[j];
    }
}

// Load the variables stored at I through I + x and store them in registers
void op_Fx65() {
    uint8_t x = (opcode & 0x0F00) >> 8;

    for (int j=0; j <= x; j++) {
        V[j] = memory[I + j];
    }
}
