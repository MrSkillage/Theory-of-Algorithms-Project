all: bitoperations cmdargs func2 preproc

bitoperations: bit-operations.c
	gcc -o bitoperations bit-operations.c

cmdargs: cmdargs.c
	gcc -o cmdargs cmdargs.c

func2: func2.c
	gcc -o func2 func2.c

preproc: preproc.c
	gcc -o preproc preproc.c