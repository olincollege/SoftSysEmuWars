struct chip8_cpu {
    unsigned short opcode; // shorts are two bytes, so are opcodes

    unsigned char memory[4096]; 
    unsigned char V[16]; // CPU registers use chars because a char is 1 byte/8 bits

    unsigned short I; // index register
    unsigned short PC; // program counter

    unsigned char display[64*32]; // store the state of each pixel;

    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned short stack[16];
    unsigned short stack_pointer; 

    unsigned char keys[16]; // store the states of the keys
};