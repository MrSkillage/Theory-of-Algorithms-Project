#include <stdio.h>

void bin_print(unsigned int i) {
    // Number of bits in an integer
    int j = sizeof(unsigned int) * 8;
    int k;
    // Loop the number of bits in i, left to right
    for (j--; j >= 0; j--) {
        // Pick out the j^th bit of i
        k = ((1 << j) & i) ? 1 : 0;
        printf("%d", k);
    }

}

// Main method signature
int main(int argc, char *argv[]) {
    
    // Set i to a literal value where '0x' specifies Hexadecimal
    unsigned int i = 0x0f0f0f;

    printf("Original:\t");
    // Print i in Binary
    bin_print(i);
    
    printf("\t%x\t%u\n\n", i, i);

    // 32 long
    int j = sizeof(unsigned int) * 8;

    for (j--; j>=0; j--) {
        // 1 gets shifted to the left j times
        bin_print(1 << j);
        printf("\n");

        // i
        bin_print(i);
        printf("\n");

        printf("-------------------------------- &\n");

        // (1 is shifted to the left j times) bitwise logical and i
        bin_print((1 << j) & i);
        printf("\n\n");
    }

    return 0;
}
