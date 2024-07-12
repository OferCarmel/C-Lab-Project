#include <stdio.h>
#include <stdlib.h>

int dec_to_bin(int, int);

main()
{
	dec_to_bin(10, 10);
	return 1;
	//testing 2 changes 
}

int dec_to_bin(int dec, int size)
{
	char* num = (char*)malloc(size * sizeof(char));
	char negative = 0;

	if (num == NULL) {
		printf("Memory allocation failed\n");
		return -1;  // Return an error code
	}

	if(num)
		num += size - 1;

	while (num>=0)
	{
		*num = dec & 1;
		dec = dec >> 1;
		num--;
	}

	for (int i = 0; i < size; i++)
	{
		printf("%d", *num);
	}
	return 1;
	// my changes
}