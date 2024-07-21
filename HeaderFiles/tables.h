#include <stdio.h>
#include <stdlib.h>
#define OPCODES_NUM 16
#define REG_NUM 8
#define INSTRUCTIONS_NUM 4
#define MACROS_NUM 2

/* ****************************** OPCODES , registers, instructions ******************************* */

/* structure for opcodes */

typedef struct {
    char* name;
    int value;
} Opcode;

/* Opcodes table */

Opcode OPCODES[OPCODES_NUM] = {
        {"mov",  0},
        {"cmp",  1},
        {"add",  2},
        {"sub",  3},
        {"lea",  4},
        {"clr",  5},
        {"not",  6},
        {"inc",  7},
        {"dec",  8},
        {"jmp",  9},
        {"bne",  10},
        {"red",  11},
        {"prn",  12},
        {"jsr",  13},
        {"rts",  14},
        {"stop", 15}
};

/* registers */
char* REGS[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };


/* instructions */
char* INSTUCTIONS[] = { ".data", ".string", ".entry", ".extern" };

/* saved macro words */

char* MACROS[] = { "endmacr", "macr" };

int is_macro(char* str);

int find_opcode_value(char* name);


int find_register(char* str);

int is_instruction(char* str);