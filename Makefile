CC=gcc
CFLAGS=-o

EXECS= main

all: $(EXECS)

main: cmdargs.c
	$(CC) $(CFLAGS) $@ $^

clean:
	rm -f $(EXECS)
