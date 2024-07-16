#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_processor.h"

char *strdup(const char *s) {
    char *d = (char *)malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

void read_file(const char *filename, LineNode **lines_head) {
    FILE *file;
    LineNode *current;
    char buffer[MAX_LINE_LENGTH];

    file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    *lines_head = NULL;
    current = NULL;

    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        LineNode *new_node = (LineNode *)malloc(sizeof(LineNode));
        if (new_node == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        new_node->line = strdup(buffer);
        if (new_node->line == NULL) {
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        new_node->next = NULL;

        if (*lines_head == NULL) {
            *lines_head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    fclose(file);
}

Macro *create_macro(const char *name) {
    Macro *macro = (Macro *)malloc(sizeof(Macro));
    if (macro == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strcpy(macro->name, name);
    macro->value = (char **)malloc(sizeof(char *) * 10);
    if (macro->value == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    macro->value_count = 0;
    macro->value_capacity = 10;
    macro->next = NULL;
    return macro;
}

void add_line_to_macro(Macro *macro, const char *line) {
    if (macro->value_count >= macro->value_capacity) {
        macro->value_capacity *= 2;
        macro->value = (char **)realloc(macro->value, sizeof(char *) * macro->value_capacity);
        if (macro->value == NULL) {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }
    macro->value[macro->value_count++] = strdup(line);
    if (macro->value[macro->value_count - 1] == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}

void parse_macros(LineNode *lines, Macro **macros_head, LineNode **non_macro_lines_head) {
    Macro *current_macro;
    LineNode *non_macro_current;

    *macros_head = NULL;
    *non_macro_lines_head = NULL;
    current_macro = NULL;
    non_macro_current = NULL;

    while (lines) {
        if (strncmp(lines->line, "macr", 4) == 0) {
            char macro_name[MAX_LINE_LENGTH];
            sscanf(lines->line, "macr %s", macro_name);
            current_macro = create_macro(macro_name);
            current_macro->next = *macros_head;
            *macros_head = current_macro;
        } else if (strncmp(lines->line, "endmacr", 7) == 0) {
            current_macro = NULL;
        } else if (current_macro) {
            add_line_to_macro(current_macro, lines->line);
        } else {
            LineNode *new_node = (LineNode *)malloc(sizeof(LineNode));
            if (new_node == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            new_node->line = strdup(lines->line);
            if (new_node->line == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            new_node->next = NULL;

            if (*non_macro_lines_head == NULL) {
                *non_macro_lines_head = new_node;
            } else {
                non_macro_current->next = new_node;
            }
            non_macro_current = new_node;
        }
        lines = lines->next;
    }
}

void replace_macros(LineNode *non_macro_lines, Macro *macros, LineNode **replaced_lines_head) {
    LineNode *replaced_current;

    *replaced_lines_head = NULL;
    replaced_current = NULL;

    while (non_macro_lines) {
        int replaced = 0;
        Macro *macro;
        for (macro = macros; macro != NULL; macro = macro->next) {
            if (strstr(non_macro_lines->line, macro->name)) {
                int i;
                for (i = 0; i < macro->value_count; i++) {
                    LineNode *new_node = (LineNode *)malloc(sizeof(LineNode));
                    if (new_node == NULL) {
                        perror("Failed to allocate memory");
                        exit(EXIT_FAILURE);
                    }
                    new_node->line = strdup(macro->value[i]);
                    if (new_node->line == NULL) {
                        perror("Failed to allocate memory");
                        exit(EXIT_FAILURE);
                    }
                    new_node->next = NULL;

                    if (*replaced_lines_head == NULL) {
                        *replaced_lines_head = new_node;
                    } else {
                        replaced_current->next = new_node;
                    }
                    replaced_current = new_node;
                }
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            LineNode *new_node = (LineNode *)malloc(sizeof(LineNode));
            if (new_node == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            new_node->line = strdup(non_macro_lines->line);
            if (new_node->line == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            new_node->next = NULL;

            if (*replaced_lines_head == NULL) {
                *replaced_lines_head = new_node;
            } else {
                replaced_current->next = new_node;
            }
            replaced_current = new_node;
        }
        non_macro_lines = non_macro_lines->next;
    }
}

void write_file(const char *filename, LineNode *lines) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    while (lines) {
        fputs(lines->line, file);
        lines = lines->next;
    }

    fclose(file);
}

void free_lines(LineNode *lines) {
    while (lines) {
        LineNode *tmp = lines;
        lines = lines->next;
        free(tmp->line);
        free(tmp);
    }
}

void free_macros(Macro *macros) {
    while (macros) {
        Macro *tmp = macros;
        int i;
        macros = macros->next;
        for (i = 0; i < tmp->value_count; i++) {
            free(tmp->value[i]);
        }
        free(tmp->value);
        free(tmp);
    }
}

void process_file(const char *input_filename, const char *output_filename) {
    LineNode *lines;
    Macro *macros;
    LineNode *non_macro_lines;
    LineNode *replaced_lines;

    lines = NULL;
    read_file(input_filename, &lines);

    macros = NULL;
    non_macro_lines = NULL;
    parse_macros(lines, &macros, &non_macro_lines);

    replaced_lines = NULL;
    replace_macros(non_macro_lines, macros, &replaced_lines);

    write_file(output_filename, replaced_lines);

    free_lines(lines);
    free_lines(non_macro_lines);
    free_lines(replaced_lines);
    free_macros(macros);
}
