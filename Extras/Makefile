CC=gcc
CFLAGS=-o

all: bitoperations cmdargs cmdargs2 func2 preproc sha256

bitoperations: bit-operations.c
	$(CC) ${CFLAGS} bitoperations bit-operations.c

cmdargs: cmdargs.c
	$(CC) ${CFLAGS} cmdargs cmdargs.c

sha256.o: sha256.c sha256.h
	$(CC) ${CFLAGS} -c sha256.c

cmdargs2: cmdargs2.c sha256.o
	$(CC) ${CFLAGS} $@ $^

func2: func2.c
	$(CC) ${CFLAGS} func2 func2.c

preproc: preproc.c
	$(CC) ${CFLAGS} preproc preproc.c

sha256: sha256.c
	$(CC) ${CFLAGS} sha256 sha256.c
