#include <stdio.h>

void bin_print(int i) {
    // Number of bits in an integer
    int j = sizeof(int) * 8;

    // Temporary Variable
    int k;

    for (j--; j>= 0; j--) {
        k = ((1 << j) & i) ? 1 : 0;
        printf("%d", k);
    }

}

int main(int argc, char *argv[]) {
    
    // Print Hello, World!
    printf("%s\n", "Hello, World again!");
    
    int i = 241;
    bin_print(i);

    printf("\n");

    for (int j = 0; j<40; j++) {
        // What the operation is
        printf("%3d << &2d: ", i, j);
        // i shifted left j times
        bin_print(i << j);
        // End line
        printf("\n");
    }

    return 0;
}
