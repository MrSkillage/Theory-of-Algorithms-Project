CC=gcc
CFLAGS=-o

EXECS= main
BINS= libsha256.o 

all: $(BINS) $(EXECS)

libsha256.o: sha256.c sha256.h
	$(CC) -c sha256.c $(CFLAGS) libsha256.o

sha256: libsha256.o
	$(CC) $^ $(CFLAGS) $@

main: cmdargs2.c sha256
	$(CC) $^ $(CFLAGS) $@ 


#sha512: sha512.c
#	$(CC) $(CFLAGS) sha512 sha512.c

#sha256: sha256.c sha256.h
#	$(CC) $(CFLAGS) sha256 sha256.c

#libsha256.o: sha256.c sha256.h
#	$(CC) $(CFLAGS) -c sha256.c

#testsha256: sha256 input.txt
#	./sha256 input.txt

#main: cmdargs2.c 
#	$(CC) $(CFLAGS) cmdargs2 cmdargs2.c

clean:
	rm -f *.o
	rm -f *.a
	rm -f ./-c
	rm -f ./-Wall
	rm -f $(EXECS)
