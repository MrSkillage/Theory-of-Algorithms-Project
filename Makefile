all: bitoperations cmdargs func2

bitoperations: bit-operations.c
	gcc -o bitoperations bit-operations.c

cmdargs: cmdargs.c
	gcc -o cmdargs cmdargs.c

func2: func2.c
	gcc -o func2 func2.c