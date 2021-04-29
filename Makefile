CC=gcc
CFLAGS=-o

EXECS= main

all: $(EXECS)

main: cmdargs.c
	$(CC) $(CFLAGS) $@ $^

test: main input.txt tests.sh
	./tests.sh

clean:
	rm -f $(EXECS)
