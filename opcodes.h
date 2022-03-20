#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "chip-8.h"

void op_00E0();
void op_00EE();
void op_1nnn();
void op_2nnn();
void op_6xnn();
void op_7xnn();
void op_Annn();
void op_Dxyn();