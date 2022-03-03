#define START_ADDRESS = 0x200
#define FONTSET_START_ADDRESS 0x50
#define MEMORY_SIZE 0x1000  // 4096 in hex
#define MAX_GAME_SIZE (MEMORY_SIZE - START_ADDRESS)


extern unsigned short opcode; // shorts are two bytes, so are opcodes

extern unsigned char memory[MEMORY_SIZE]; 
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
void load_game(char *filename);