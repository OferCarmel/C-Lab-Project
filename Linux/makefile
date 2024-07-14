all:assembler

assembler: assembler.o pre_proc.o typedef.o
	gcc -ansi -Wall -pedantic assembler.o pre_proc.o typedef.o
	make clean

pre_proc.o: pre_proc.c pre_proc.h
	gcc -ansi -Wall -pedantic -c pre_proc.c 

assembler.o: pre_proc.c
	gcc -ansi -Wall -pedantic -c assembler.c

typedef.o: typedef.c
	gcc -ansi -Wall -pedantic -c typedef.c

clean:
	rm *.o 
