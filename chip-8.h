
extern unsigned short opcode; // shorts are two bytes, so are opcodes

extern unsigned char memory[4096]; 
extern unsigned char V[16]; // CPU registers use chars because a char is 1 byte/8 bits

extern unsigned short I; // index register
extern unsigned short PC; // program counter

extern unsigned char display[64*32]; // store the state of each pixel;

extern unsigned char delay_timer;
extern unsigned char sound_timer;

extern unsigned short stack[16];
extern unsigned short stack_pointer; 

extern unsigned char keys[16]; // store the states of the keys

void init();