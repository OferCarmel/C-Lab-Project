#include <stdio.h>

int open_macros(char* file_name)
{
	FILE* fptr;
	fptr = fopen(file_name, "r");


}
char* getword(FILE* file)
{
	char* buf;
	if (file == NULL)
	{
		buf[0] = "error cannot read file";
		return buf;
	}
	if (scanf(file, "%*s", buf) == 1)
		return buf;
	return buf;
}