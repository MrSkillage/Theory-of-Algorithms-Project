#include <stdio.h>
#include <stdlib.h>

#include "sha256.h"

typedef enum Algorithm
{
    SHA_256,
    SHA_512,
    SHA_BOTH
} Algorithm;

Algorithm ALGO = SHA_BOTH;

void Options(char *arg0)
{
    printf("Usage: %s [OPTIONS or STRING]\n", arg0);
    printf("Calculate the SHA-512 and SHA-256 has values of the file.\n");
    printf("Options:\n");
    printf("-f, --file [FILENAME] Calculate both SHA-512 and SHA-256 hash values of the file.\n");
    printf("-a, --algorithm [ALGORITHM] Calculates the given algorithm. SHA-512 = 512 or SHA-256 = 256.\n");
    printf("-h, --help Print command line options.\n\n");
    printf("Example: %s -a 256 -f input.txt \n", arg0);
    printf("\t Will perform the SHA256 hash function on the file input.txt\n");
}

void NoInput(char * arg0) {
    printf("You've Entered: [%s] with no command arguemnts.\n", arg0);
    printf("If you are unsure you can enter: [%s -h] for help with a list of commands\n", arg0);
}

/*
void getHash(FILE *F, Algorithm A, char *name) {
    if (A == SHA_256) {
        printf("Performing Hash Function [256] on File [%s] :\n", name);        
        SHA256(F);
    }

    if (A == SHA_512) {
        printf("Performing Hash Function [512] on File [%s] :\n", name);   
        printf("PERFORMING SHA512... SOME HASH VALUE\n");
    }

    if (A == SHA_BOTH) {
        printf("Performing Hash Function [256] AND [512] on File [%s] :\n", name);   
        printf("[SHA-256] : "); 
        SHA256(F);
        printf("[SHA-512] : "); 
        printf("PERFORMING SHA512... SOME HASH VALUE\n");
    }
}
*/

int main(int argc, char **argv)
{
    char name[20];
    FILE *F;
    if (argc > 1)
    {
        int inputPos = 1;
        char *flag = argv[1];
        if (flag[0] == '-')
        {
            int i;
            int argNumWithFile = -1;
            for (i = 1; i < argc; i++)
            {
                flag = argv[i];
                char c = (flag[1] == '-') ? flag[2] : flag[1];
                switch (c)
                {
                // Print and handle argv[2] as a file passed.
                case 'f':
                    if (argc > i + 1)
                    {
                        argNumWithFile = i + 1;
                        F = fopen(argv[argNumWithFile], "r");
                    }
                    break;
                // Print and handle the Algorithm choosen.
                case 'a':
                    if (argc > i + 1)
                    {
                        char *str256 = "256";
                        char *str512 = "512";
                        if (strncmp(argv[i + 1], str256, 3) == 0)
                        {
                            ALGO = SHA_256;
                        }
                        if (strncmp(argv[i + 1], str512, 3) == 0)
                        {
                            ALGO = SHA_512;
                        }
                        if (argc > i + 2)
                        {
                            inputPos = i + 2;
                        }
                    }
                    break;
                // Print the help message detailing user options.
                case 'h':
                    Options(argv[0]);
                    break;
                default:
                    break;
                }
            }
            if (argNumWithFile > -1)
            {
                //if (F != NULL) getHash(F, ALGO, argv[argNumWithFile]);
                inputPos = argc + 1;
            }
        }
        if (inputPos < argc)
        {
            //printf("Performing Hashing Algorithm on string passed.\n");
        }
    }
    else
    {
        NoInput(argv[0]);
    }
    
    if (F != NULL)
        fclose(F);
    
    return 0;
}