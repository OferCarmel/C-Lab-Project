#include <stdio.h>
#include <stdlib.h>
#include "pre_proc.h"

char* dec_to_bin(int, int);

int main()
{
	FILE* fptr;
	FILE* wrfile;

	char* word = (char*)malloc(sizeof(char) * 81);
	char* space = " ";
	fptr = fopen("asembley_code.as", "r");
	wrfile = fopen("output", "w");


	while (getc(stdin) == '\n')
	{
		if (get_word(fptr, word) != NULL)
		{
			printf("%s ", word);
			put_word(wrfile, word);
			put_word(wrfile, space);
		}
		else
			printf("error getting word \n");
	}

	fclose(fptr);
	fclose(wrfile);


	return 1;
}






	char* dec_to_bin(int dec, int size)
	{
		char* num = (char*)malloc(size * sizeof(char));
		char* num_start = num;
		char i;


		if (num == NULL) {
			printf("Memory allocation failed\n");
			return NULL;  /* Return an error code*/
		}

		if(num)   /*insert into num from the end*/
			*num +=(char)size - 1;

		while (num >= num_start) {
			*num = dec & 1;
			dec = dec >> 1;
			num--;
		}

		 /*Print the binary number for verification*/
		for (i = 0 ; i < size; i++) {
			printf("%d", num[i]);
		}
		return num_start;
	}