all: bitoperations cmdargs

bitoperations: bit-operations.c
	gcc -o bitoperations bit-operations.c

cmdargs: cmdargs.c
	gcc -o cmdargs cmdargs.c