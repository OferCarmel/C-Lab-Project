#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/file_operations.h"


/* open a file and return the FILE pointer */

FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r");  /* try to open the file in read mode */
    if (file == NULL) {
        printf("File: %s \n", filename);
        perror("Error opening file #"); /* error if file cannot be opened */
        return NULL; /* Return NULL on failure */
    }
    printf("File opened successfully.\n"); /* Inform the user that the file is open */
    return file; /* Return the file pointer on success */
}

/* close a file and return status code */
int closeFile(FILE* file)
{
    if (file == NULL) 
    {
        fprintf(stderr, "Error: No file to close.\n");
        return -1; /* Return -1 if no file was provided */
    }
    fclose(file); /* try to close the file */
    printf("File closed successfully.\n"); /* Confirm that the file is closed */
    return 0; /* Return 0 on successful close */
}


/*we must check the case where a line from souce file is > 80 (or 81 with \n)
  which fgets does not check, so i mad a custom function - get_line()  */
/*  to read a single line from a file, up to 80 characters */
char* readLine(FILE* file) 
{
    if (file == NULL)
    {
        fprintf(stderr, "Error: File is not opened.\n");
        return NULL;
    }

    char* buffer = malloc(81); /* Allocate memory for the buffer, 80 chars + 1 for '\0' */
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    if (fgets(buffer, 81, file) == NULL)
    {
        free(buffer); /* Free memory if end of file or error occurs */
        return NULL; /* Return NULL on end of file or error */
    }
    return buffer; /* Return the line read from the files */
}

/*must get recieve buffet size of 82 */
char* get_line(FILE* file)
{
    char* buffer = malloc(sizeof(char) * (MAX_LINE_LENGTH + 2)); /* Allocate memory for the buffer, 80 chars + 2 for '\n', '\0' */
    char* start = buffer;
    char c;
    if (file == NULL)
    {
        fprintf(stderr, "Error: File is not opened.\n");
        return NULL;
    }
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    while ((c = getc(file)) != EOF)
    {
        if (buffer - start >= MAX_LINE_LENGTH && c != '\n') /*char 81 can be '\n' */
        {
            perror("error, line read > 80 characters\n");
            free(buffer);
            return NULL;
        }
        if (c == '\n')
        {
            *(buffer++) = c;
            break;
        }
        else
            *(buffer++) = c;
    }
    *buffer = '\0';
    if (c == EOF && buffer - start == 0)
    {
        printf("\n");
        return NULL;    /* returns NULL in case only EOF is read*/
    }
    return start;
}

char* get_word(char* line)
{
    char* start, *end = line, *new_word;
    char size, c;
    char is_word = 0;
    int i = 0;
    printf("%s\n", line);

    while (*line != '\0' && is_word != 2)
    {
        switch (*line)
        {
        case '\t':
        case ' ':
        case '\n':
        case '\0':
            if (is_word)
            {
                end = line;
                is_word++;
            }
            else
                line++;
            break;

        default:
            if (!is_word) 
            {
                is_word = 1;
                start = line;
            }
            line++;
        }
    }
    if (!is_word)
        return NULL;
    size = end - start;

    new_word = malloc(sizeof(char) * (size + 1));
    
    if (new_word == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    for (; start < end;)  /*copy word from line to new string*/
    {
        *new_word++ = *start++;
    }
    *new_word = '\0';
    
    return new_word - (size);
}
