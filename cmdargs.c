#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sha256.c"
#include "sha512.c"

// Enum for Algorithm selection
typedef enum Algorithm
{
    SHA_256,
    SHA_512
} Algorithm;

// Set default Algorithm to SHA512
Algorithm ALGO = SHA_512;

void Options(char *arg0)
{
    printf("Usage: %s [OPTIONS or STRING]\n", arg0);
    printf("Calculate the SHA-512 and SHA-256 hash values of the file.\n");
    printf("Options:\n");
    printf("-f, --file [FILENAME] Calculate both SHA-512 and SHA-256 hash values of the file.\n");
    printf("-a, --algorithm [ALGORITHM] Calculates the given algorithm. SHA-512 = 512 or SHA-256 = 256.\n");
    printf("-h, --help Print command line options.\n\n");
    printf("Example: %s -a 256 -f input.txt \n", arg0);
    printf("\t Will perform the SHA256 hash function on the file input.txt\n");
}

void NoInput(char *arg0) {
    printf("You've Entered: [%s] with no command arguemnts.\n", arg0);
    printf("If you are unsure you can enter: [%s -h] for help with a list of commands\n", arg0);
}

void NeedsOptionValue(char *arg0) {
    printf("You have presented an optional command with no value, option needs a value.\n");
    printf("For example you could try [%s -a 256] for setting the SHA256 Algorithm.\n", arg0);
    printf("Or [%s -f text.txt] to set your file.\n", arg0);
}

void InvalidAlgo(char *arg0) {
    printf("Invalid Algo type! User needs to enter either [256] for the SHA256 Algorithm or [512] for the SHA512 Algorithm.\n");
    printf("Example: [%s -a 256] or [%s -a 512].\n", arg0, arg0);
}

void getFileHash(FILE *F, Algorithm A, char *name) {
    if (A == SHA_256) {
        printf("Performing Hash Function [256] on File [%s] :\n", name);        
        SHA256(F);
    }

    if (A == SHA_512) {
        printf("Performing Hash Function [512] on File [%s] :\n", name);   
        SHA512(F);
    }
}

int main(int argc, char **argv) {

    FILE *F;
    int c;

    while( ((c = getopt(argc, argv, ":a:f:h")) != -1)){ //get option from the getopt() method
      switch(c){
         //For option i, r, l, print that these are options
         case 'h':
            Options(argv[0]);
            break;
         case 'a': //here f is used for some file name
            if (strncmp(optarg, "256", 3) == 0) ALGO = SHA_256;
            else if (strncmp(optarg, "512", 3) == 0) ALGO = SHA_512;
            else InvalidAlgo(argv[0]);
            break;   
         case 'f': //here f is used for some file name
            F = fopen(optarg, "r");
            getFileHash(F, ALGO, optarg);
            break;
         case ':':
            NeedsOptionValue(argv[0]);
            break;
         case '?': //used for some unknown options
            printf("unknown option: %c\n", optopt);
            break;
        }
    }

    for (; optind < argc; optind++) {
        printf("Extra arguements: %s\n", argv[optind]);
    }

    if (F != NULL) {
        fclose(F);
    }

    return 0;
}