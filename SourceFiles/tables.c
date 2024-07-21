#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/tables.h"


/* ****************************** OPCODES , registers, instructions ******************************* */

/* TBD - create .h file */

/* structure for opcodes */

/* Opcodes table */

/* registers */


int is_macro(char* str) {
    int x;

    /* Return -1 if the str is NULL */
    if (str == NULL) {
        return -1;
    }

    for (x = 0; x < MACROS_NUM; x++) {
        if (strcmp(str, MACROS[x]) == 0) {
            return x; /* Return the index of the matching register */
        }
    }
    return -1; /* Return -1 if the string does not match any of our register */
}



int find_opcode_value(char* name) {
    int i;

    /* Return -1 if str is NULL */
    if (name == NULL)
    {
        return -1;
    }
    /* Iterate through the list of opcodes and compare the str with each opcode */
    for (i = 0; i < OPCODES_NUM; i++) {
        if (strcmp(OPCODES[i].name, name) == 0) {
            return OPCODES[i].value; /* return the opcode value by opcodes table*/
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