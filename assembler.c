#include <stdio.h>
#include <stdlib.h>
#include "pre_proc.c"

int dec_to_bin(int, int);

main()
{
	FILE* fptr;
	fptr = fopen("asembley_code.as", "r");
	char* a = getword(fptr);

	printf("%s", a);
	return 1;
}


int dec_to_bin(int dec, int size)
{
	char* num = (char*)malloc(size * sizeof(char));
	char* num_start = num;
	char i = 0;
 
	char negative = 0;

	if (num == NULL) {
		printf("Memory allocation failed\n");
		return -1;  /* Return an error code*/
	}

	if(num)   /*insert into num from the end*/
		num += size - 1;
	int delta;

	while (num >= num_start) {
		*num = dec & 1;
		dec = dec >> 1;
		num--;
	}

	 /*Print the binary number for verification*/
	for (int i = 0; i < size; i++) {
		printf("%d", num_start[i]);
	}
	return 1;
	/*my changes*/
}