#include <stdio.h>
#include <stdlib.h>

/* open a file and return the FILE pointer */
FILE* openFile(const char* filename) {
    FILE* file = fopen(filename, "r");  /* try to open the file in read mode */
    if (file == NULL) {
        perror("Error opening file"); /* error if file cannot be opened */
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
