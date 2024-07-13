#ifndef FILE_OPERATIONS_H 
#define FILE_OPERATIONS_H
#include <stdio.h> 

/* Function prototypes */

/* Opens a file in read mode, return A pointer to FILE on success; NULL on failure */
FILE* openFile(const char* filename);

 /* Closes an opened file - return 0 on successful close, -1 if the file was NULL. */
int closeFile(FILE* file);

/* Reads a single line from a file, up to 80 characters.
  return A pointer to FILE on success; NULL on failure */
char* readLine(FILE* file);

#endif /* FILE_OPERATIONS_H */
