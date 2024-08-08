#include <stdio.h>
#include <stdlib.h>
#define OPCODES_NUM 16
#define REG_NUM 8
#define INSTRUCTIONS_NUM 4

#define MAX_LABEL_LENGTH 31


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

/* Function to check if a string is a valid label - ends with " : " and only with chars/numbers */
bool isValidLabel(char* str)
{
    unsigned int i;
    unsigned int len;

    /* Check if the string is empty or NULL */
    if (str == NULL || *str == '\0') 
        return false;

    /* Check if the string ends with a colon */
    len = strlen(str);
    if (str[len - 1] != ':') 
        return false;

    /* Check if the first character is a small or upper letter */
    if (!isalpha((unsigned char)str[0])
        return false;

    /* Check the rest of the string for valid identifier characters */
    for (i = 1; i < len - 1; i++)
    {
        if (!isalnum((unsigned char)str[i])) 
        {
            return false;
        }
    }
    return true;
}

/* check if a line starts with ";" if it does then this line is a note line*/
bool isNoteLine(const char* line, char ch) {
    return line[0] == ch; 
}

/* Function to check if a line contains only tabs or spaces if it does - its an "empty sentence" */
bool isOnlyTabsOrSpaces(const char* line) {
    int i;
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t') {
            return false;
        }
    }
    return true;
}


/* TBD!! check if label is different than any old macro + label does not repeat twice in the file */
/* Function to check if a given string is Unique and legal */
bool LabelIsNotInList(const char* str) {
    int listSize;
    int i;

    const char* list[] = {
        "mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec",
        "jmp", "bne", "red", "prn", "jsr", "rts", "stop", "r0", "r1",
        "r2", "r3", "r4", "r5", "r6", "r7", "macr", "endmacr", "data",
        "string", "entry", "extern"};

    listSize = sizeof(list) / sizeof(list[0]);

    for (i = 0; i < listSize; i++) {
        if (strcmp(str, list[i]) == 0) {
            return false;
        }
    }
    return true;
}

/* Function to check if a given string is ".data" or ".entry" */
bool isDataOrEntry(const char* str) {
    return (strcmp(str, ".data") == 0 || strcmp(str, ".entry") == 0);
}


 /* Structure to represent a label and its value */
typedef struct Label {
    char name[MAX_LABEL_LENGTH];
    int value; 
    struct Label* next;
}Label;
/* linked list must be named label_table: */
    Label* label_table = NULL

/* Function to check if a label is already in the label table */
bool isLabelUnique(const char* label) {
    Label* current = label_table;
    while (current != NULL) {
        if (strcmp(current->name, label) == 0) {
            return false;
        }
        current = current->next;
    }
    return true;
}

/* Function to add a label to the label table */
bool addLabel(char* label, int value) {
    if (isLabelUnique(label) && LabelIsNotInList(label)) {
        Label* newLabel = (Label*)malloc(sizeof(Label));
        if (newLabel == NULL) {
            printf("Error: Memory allocation failed.\n"); /* add matching error from error list */
            return false;
        }
        strcpy(newLabel->name, label);
        newLabel->value = value;
        newLabel->next = label_table;
        label_table = newLabel;
        return true;
    }
    return false;
}

/* Function to free the memory allocated for the label table */
void freeLabelTable() {
    Label* current = label_table;
    while (current != NULL) {
        Label* next = current->next;
        free(current);
        current = next;
    }
}
