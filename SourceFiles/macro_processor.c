#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HeaderFiles/macro_processor.h"
#include "../HeaderFiles/file_operations.h"
#include "../HeaderFiles/tables.h"


char* MACROS[] = {"macr", "endmacr"};

/*should add:
  check if macro name is saved words
  
  check if macro name already exists
  */
char *strdup(const char *s) {
    char *d = (char *)malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
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
/*
char search_macro_name(macro* macro)
{

}
*/
char check_macro_name(char* name)
{
    if (is_instruction(name) == 0 && is_macro(name) == -1 && find_register(name) == -1 && find_opcode_value(name) == -1)
    {
        return 1;
    }
    return 0;
}

void scan_file(const char *input_filename, const char *output_filename) {
    LineNode *lines;
    Macro *macros;
    WordNode* firstWord = NULL;
    char* buffer = NULL, *word = NULL;
    FILE* file = openFile(input_filename);
    lines = NULL;
    macros = NULL;
    char in_macro = 0;

    buffer = get_line(file);
    if (buffer == NULL)
        perror("Failed to allocate memory");

    while (word = get_word(buffer) != NULL)
    {
        if (!newStructNode(firstWord, word)) /*saves all words in WordNode*/
            exit(EXIT_FAILURE);   /*if mem alloc failed*/
    }

    if (firstWord->word == MACROS[0])  /*check if needs to  start macro*/
    {
        if (firstWord->pos != 2) /*check if line is not 2 words only*/
        {
            perror("Error in macro deffinition");
        }
        if (!check_macro_name(getWordByIndex(firstWord, 1))) /*if macro name is bad*/
        {
            perror("Error in macro name");
        }
    }

    write_file(output_filename, replaced_lines);

    free_lines(lines);
    free_lines(non_macro_lines);
    free_lines(replaced_lines);
    free_macros(macros);
}


/* function returns the next word of the file.
   ignores spacesreturns EOF if    */

char record_macro(FILE* file)
{
    LineNode* firstLine = NULL;
    WordNode* fistWord = NULL;
    char* line = malloc(sizeof(char) * (MAX_LINE_LENGTH + 2));
    line = get_line(file);

}

int put_word(FILE* file, char* word)
{
    if (fputs(word, file) != EOF)
        return 1;

    printf("error writing into file");
    return 0;
}

/*creates new word struct. pos number of the word in th sentence (last = 1)*/
char newStructNode(WordNode* node, char* word)
{
    if (node->next == NULL)
    {
        node = (WordNode*)malloc(sizeof(WordNode));
        if (node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 0;
        }
        node->word = word;
        node->pos++;
        node->next = NULL;
        return 1;
    }
    if (newStructNode(node->next, word))
        node->pos++;
    return 1;
}

char* getWordByIndex(WordNode* node, char number)
{
    if (number == 0 != node->next == NULL)
        return node->word;
    return getWordByIndex(node->next, number--);
}
