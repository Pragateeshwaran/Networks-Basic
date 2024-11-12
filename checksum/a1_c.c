#include <stdio.h>
#include <string.h>

int binaryToDecimal(const char *binary) {
    int decimal = 0;
    int length = strlen(binary);
    
    for (int i = 0; i < length; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    
    return decimal;
}

int main() {
    const char *binary = "1011";
    int decimal = binaryToDecimal(binary);
    printf("Binary: %s -> Decimal: %d\n", binary, decimal);
    return 0;
}



#include <stdio.h>

void decimalToBinary(int decimal) {
    if (decimal == 0) {
        printf("0");
        return;
    }

    int binary[32];  // Assuming a 32-bit integer
    int index = 0;

    while (decimal > 0) {
        binary[index++] = decimal % 2;
        decimal /= 2;
    }

    // Print binary number in reverse order
    for (int i = index - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }
}

int main() {
    int decimal = 11;
    printf("Decimal: %d -> Binary: ", decimal);
    decimalToBinary(decimal);
    printf("\n");
    return 0;
}
