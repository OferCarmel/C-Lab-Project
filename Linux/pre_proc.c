#include <stdio.h>

/*
int open_macros(char* file_name)
{
	FILE* fptr;
	fptr = fopen(file_name, "r");

	return 1;
}
*/

/*use fscanf to get word, loses /n character */

/*
char* get_word(FILE* file, char* buffer) {

	 Read the first word from the file
	if (fscanf(file, "%s", buffer) == 1)
		return buffer;
	else
		return NULL;  Return NULL if no word is found
}
*/


/* function returns the next word of the file. 
   ignores spacesreturns EOF if    */
char* get_word(FILE* file, char* buffer)
{
	char* start = buffer;
	char c;
	char is_word = 0;
	while ((c = getc(file)) != EOF)
	{
		switch (c)
		{
		case '\t':
			if (!is_word)
				break;
			*buffer = '\0';
			return start;

		case ' ':
			if (!is_word)
				break;
			*buffer = '\0';
			return start;

		case '\n':
			if (!is_word)
				break;
			*buffer++ = c;
			*buffer = '\0';
			return start;

		default:
			is_word = 1;
			*buffer++ = c;
		}
	}
	if (!is_word)
		return NULL;
	buffer++;
	*buffer = '\0';
	return start;
}

int put_word(FILE* file, char* word)
{
	if (fputs(word, file) != EOF)
		return 1;

	printf("error writing into file");
	return 0;
}