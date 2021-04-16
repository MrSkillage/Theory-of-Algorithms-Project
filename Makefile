all: sha512

sha512: sha512.c
	gcc -o sha512 sha512.c