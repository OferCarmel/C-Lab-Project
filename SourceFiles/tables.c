#include <stdio.h>
#include <stdlib.h>
#define OPCODES_NUM 16
#define REG_NUM 8
#define INSTRUCTIONS_NUM 4

/* ****************************** OPCODES , registers, instructions ******************************* */

/* TBD - create .h file */

/* structure for opcodes */
typedef struct {
    char* name;
    int value;
} Opcode

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
char* INSTUCTIONS[] = { ".data", ".string", ".entry", ".extern"};



int find_opcode_value(char* name) {
    int i;

    /* Return -1 if str is NULL */
    if (str == NULL)
    {
        return -1;
    }
    /* Iterate through the list of opcodes and compare the str with each opcode */
    for (i = 0; i < NUM_OPCODES; i++) {
        if (strcmp(opcodes[i].name, name) == 0) {
            return opcodes[i].value; /* return the opcode value by opcodes table*/
        }
    }
    return -1; /* Return -1 if opcode is not found */
}


int find_register(char *str) {
    int x;

    /* Return -1 if the str is NULL */
    if (str == NULL) {
        return -1;
    }

    /* Iterate through the list of registers and compare the string with each register */
    for (x = 0; x < REG_NUM; x++) {
        if (strcmp(str, REGS[x]) == 0) {
            return x; /* Return the index of the matching register */
        }
    }
    return -1; /* Return -1 if the string does not match any of our register */
}

int is_instruction(char* str) {
    int i;

    /* Return 0 if the string is NULL */
    if (str == NULL) {
        return 0;
    }

    /* Iterate through the list of known instructions and compare the string with each instruction in the list */
    for (i = 0; i < INSTRUCTIONS_NUM; i++) {
        if (strcmp(str, INSTUCTIONS[i]) == 0) {
            return 1; /* Return 1 if the string matches an instruction */
        }
    }
    return 0; /* Return 0 if the string is not an instruction */
}