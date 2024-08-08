#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_processor.h"

/* Function to duplicate a string */
char* strdup(const char* s) {
    /* Allocate memory for the duplicate string */
    char* d = (char*)malloc(strlen(s) + 1);
    if (d == NULL) return NULL; /* Check for allocation failure */
    strcpy(d, s); /* Copy the original string to the new memory location */
    return d; /* Return the duplicate string */
}

/* Function to read a file and store its lines in a linked list */
void read_file(const char* filename, LineNode** lines_head) {
    FILE* file;
    LineNode* current;
    char buffer[MAX_LINE_LENGTH];

    file = fopen(filename, "r"); /* Open the file for reading */
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE); /* Exit if file cannot be opened */
    }

    *lines_head = NULL;
    current = NULL;

    /* Read the file line by line */
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        LineNode* new_node = (LineNode*)malloc(sizeof(LineNode)); /* Allocate memory for a new node */
        if (new_node == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE); /* Exit if memory allocation fails */
        }
        new_node->line = strdup(buffer); /* Duplicate the line and store it in the new node */
        if (new_node->line == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE); /* Exit if memory allocation fails */
        }
        new_node->next = NULL;

        if (*lines_head == NULL) {
            *lines_head = new_node; /* Set the head if it's the first node */
        }
        else {
            current->next = new_node; /* Link the new node to the previous node */
        }
        current = new_node; /* Move to the new node */
    }

    fclose(file); /* Close the file */
}

/* Function to create a macro */
Macro* create_macro(const char* name) {
    Macro* macro = (Macro*)malloc(sizeof(Macro)); /* Allocate memory for the macro */
    if (macro == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE); /* Exit if memory allocation fails */
    }
    strcpy(macro->name, name); /* Copy the macro name */
    macro->value = (char**)malloc(sizeof(char*) * 10); /* Allocate initial memory for macro values */
    if (macro->value == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE); /* Exit if memory allocation fails */
    }
    macro->value_count = 0;
    macro->value_capacity = 10;
    macro->next = NULL;
    return macro; /* Return the new macro */
}

/* Function to add a line to a macro */
void add_line_to_macro(Macro* macro, const char* line) {
    if (macro->value_count >= macro->value_capacity) {
        macro->value_capacity *= 2;
        macro->value = (char**)realloc(macro->value, sizeof(char*) * macro->value_capacity); /* Reallocate memory if needed */
        if (macro->value == NULL) {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE); /* Exit if memory allocation fails */
        }
    }
    macro->value[macro->value_count++] = strdup(line); /* Duplicate the line and store it in the macro */
    if (macro->value[macro->value_count - 1] == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE); /* Exit if memory allocation fails */
    }
}

/* Function to parse macros and non-macro lines from a list of lines */
void parse_macros(LineNode* lines, Macro** macros_head, LineNode** non_macro_lines_head) {
    Macro* current_macro;
    LineNode* non_macro_current;

    *macros_head = NULL;
    *non_macro_lines_head = NULL;
    current_macro = NULL;
    non_macro_current = NULL;

    /* Process each line */
    while (lines) {
        if (strncmp(lines->line, "macr", 4) == 0) { /* If the line starts with "macr", it's the start of a macro */
            char macro_name[MAX_LINE_LENGTH];
            sscanf(lines->line, "macr %s", macro_name); /* Extract the macro name */
            current_macro = create_macro(macro_name); /* Create a new macro */
            current_macro->next = *macros_head;
            *macros_head = current_macro;
        }
        else if (strncmp(lines->line, "endmacr", 7) == 0) { /* If the line starts with "endmacr", it's the end of a macro */
            current_macro = NULL;
        }
        else if (current_macro) { /* If we are inside a macro definition */
            add_line_to_macro(current_macro, lines->line); /* Add the line to the current macro */
        }
        else { /* If the line is not part of a macro definition */
            LineNode* new_node = (LineNode*)malloc(sizeof(LineNode)); /* Allocate memory for a new node */
            if (new_node == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE); /* Exit if memory allocation fails */
            }
            new_node->line = strdup(lines->line); /* Duplicate the line and store it in the new node */
            if (new_node->line == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE); /* Exit if memory allocation fails */
            }
            new_node->next = NULL;

            if (*non_macro_lines_head == NULL) {
                *non_macro_lines_head = new_node; /* Set the head if it's the first node */
            }
            else {
                non_macro_current->next = new_node; /* Link the new node to the previous node */
            }
            non_macro_current = new_node; /* Move to the new node */
        }
        lines = lines->next; /* Move to the next line */
    }
}

/* Function to replace macros in non-macro lines */
void replace_macros(LineNode* non_macro_lines, Macro* macros, LineNode** replaced_lines_head) {
    LineNode* replaced_current;

    *replaced_lines_head = NULL;
    replaced_current = NULL;

    /* Process each non-macro line */
    while (non_macro_lines) {
        int replaced = 0;
        Macro* macro;
        /* Check each macro to see if it needs to be replaced */
        for (macro = macros; macro != NULL; macro = macro->next) {
            if (strstr(non_macro_lines->line, macro->name)) { /* If the line contains the macro name */
                int i;
                /* Add each line of the macro definition */
                for (i = 0; i < macro->value_count; i++) {
                    LineNode* new_node = (LineNode*)malloc(sizeof(LineNode)); /* Allocate memory for a new node */
                    if (new_node == NULL) {
                        perror("Failed to allocate memory");
                        exit(EXIT_FAILURE); /* Exit if memory allocation fails */
                    }
                    new_node->line = strdup(macro->value[i]); /* Duplicate the macro line and store it in the new node */
                    if (new_node->line == NULL) {
                        perror("Failed to allocate memory");
                        exit(EXIT_FAILURE); /* Exit if memory allocation fails */
                    }
                    new_node->next = NULL;

                    if (*replaced_lines_head == NULL) {
                        *replaced_lines_head = new_node; /* Set the head if it's the first node */
                    }
                    else {
                        replaced_current->next = new_node; /* Link the new node to the previous node */
                    }
                    replaced_current = new_node; /* Move to the new node */
                }
                replaced = 1;
                break;
            }
        }
        if (!replaced) { /* If no macro replacement was made */
            LineNode* new_node = (LineNode*)malloc(sizeof(LineNode)); /* Allocate memory for a new node */
            if (new_node == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE); /* Exit if memory allocation fails */
            }
            new_node->line = strdup(non_macro_lines->line); /* Duplicate the line and store it in the new node */
            if (new_node->line == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE); /* Exit if memory allocation fails */
            }
            new_node->next = NULL;

            if (*replaced_lines_head == NULL) {
                *replaced_lines_head = new_node; /* Set the head if it's the first node */
            }
            else {
                replaced_current->next = new_node; /* Link the new node to the previous node */
            }
            replaced_current = new_node; /* Move to the new node */
        }
        non_macro_lines = non_macro_lines->next; /* Move to the next line */
    }
}

/* Function to write lines to a file */
void write_file(const char* filename, LineNode* lines) {
    FILE* file = fopen(filename, "w"); /* Open the file for writing */
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE); /* Exit if file cannot be opened */
    }

    /* Write each line to the file */
    while (lines) {
        fputs(lines->line, file);
        lines = lines->next;
    }

    fclose(file); /* Close the file */
}

/* Function to free the memory allocated for the linked list of lines */
void free_lines(LineNode* lines) {
    while (lines) {
        LineNode* tmp = lines;
        lines = lines->next;
        free(tmp->line); /* Free the memory allocated for the line */
        free(tmp); /* Free the memory allocated for the node */
    }
}

/* Function to free the memory allocated for the linked list of macros */
void free_macros(Macro* macros) {
    while (macros) {
        Macro* tmp = macros;
        int i;
        macros = macros->next;
        for (i = 0; i < tmp->value_count; i++) {
            free(tmp->value[i]); /* Free the memory allocated for each macro line */
        }
        free(tmp->value); /* Free the memory allocated for the macro value array */
        free(tmp); /* Free the memory allocated for the macro */
    }
}

/* Main function to process the file */
void process_file(const char* input_filename, const char* output_filename) {
    LineNode* lines;
    Macro* macros;
    LineNode* non_macro_lines;
    LineNode* replaced_lines;

    lines = NULL;
    read_file(input_filename, &lines); /* Read the input file into a linked list of lines */

    macros = NULL;
    non_macro_lines = NULL;
    parse_macros(lines, &macros, &non_macro_lines); /* Parse the macros and non-macro lines */

    replaced_lines = NULL;
    replace_macros(non_macro_lines, macros, &replaced_lines); /* Replace macros in the non-macro lines */

    write_file(output_filename, replaced_lines); /* Write the replaced lines to the output file */

    free_lines(lines); /* Free the memory allocated for the lines */
    free_lines(non_macro_lines); /* Free the memory allocated for the non-macro lines */
    free_lines(replaced_lines); /* Free the memory allocated for the replaced lines */
    free_macros(macros); /* Free the memory allocated for the macros */
}
