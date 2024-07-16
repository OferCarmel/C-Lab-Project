#ifndef MACRO_PROCESSOR_H

#define MACRO_PROCESSOR_H



#define MAX_LINE_LENGTH 256



/* Struct to represent a macro */

typedef struct Macro {

    char name[MAX_LINE_LENGTH];

    char** value;

    int value_count;

    int value_capacity;

    struct Macro* next;

} Macro;



/* Struct to represent a line node in a linked list */

typedef struct LineNode {

    char* line;

    struct LineNode* next;

} LineNode;



/* Function declarations */

char* strdup(const char* s);

void read_file(const char* filename, LineNode** lines_head);

Macro* create_macro(const char* name);

void add_line_to_macro(Macro* macro, const char* line);

void parse_macros(LineNode* lines, Macro** macros_head, LineNode** non_macro_lines_head);

void replace_macros(LineNode* non_macro_lines, Macro* macros, LineNode** replaced_lines_head);

void write_file(const char* filename, LineNode* lines);

void free_lines(LineNode* lines);

void free_macros(Macro* macros);

void process_file(const char* input_filename, const char* output_filename);



#endif /* MACRO_PROCESSOR_H */
