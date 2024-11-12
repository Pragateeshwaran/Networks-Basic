#include <stdio.h>

void printBinary(int n) {
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0) printf(" ");  // For readability, add spaces every 4 bits
    }
    printf("\n");
}

int main() {
    int number = -17;
    printf("Binary representation of %d:\n", number);
    printBinary(number);
    return 0;
}
