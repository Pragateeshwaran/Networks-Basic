#include <stdio.h>
#include <math.h>

int dataWord[32];
int hammingCode[32];
int originalCode[32];  // New array to store the original hamming code

int calculateParity(int position, int codeLength, int code[]);  // Modified function signature

int main() {
    int dataWordLength, i, parityBitsCount = 0, codeLength;
    int dataIndex, parityIndex;

    // Step 1: Input the data word length and data word itself
    printf("Please enter the length of the Data Word: ");
    scanf("%d", &dataWordLength);
    printf("Please enter the Data Word:\n");
    for(i = 0; i < dataWordLength; i++) {
        scanf("%d", &dataWord[i]);
    }

    // Step 2: Calculate the number of parity bits required using the formula m + r + 1 <= 2^r
    while (dataWordLength + parityBitsCount + 1 > (int)pow(2, parityBitsCount)) {
        parityBitsCount++;
    }

    // Step 3: Calculate the total length of the codeword
    codeLength = dataWordLength + parityBitsCount;

    // Step 4: Place the data bits and initialize the parity bits
    dataIndex = parityIndex = 0;
    for(i = 0; i < codeLength; i++) {
        if(i == ((int)pow(2, parityIndex) - 1)) {
            hammingCode[i] = 0;  // Parity bit, initially set to 0
            parityIndex++;
        } else {
            hammingCode[i] = dataWord[dataIndex];
            dataIndex++;
        }
    }

    // Step 5: Calculate and place the parity bits
    for(i = 0; i < parityBitsCount; i++) {
        int position = (int)pow(2, i);
        int parityValue = calculateParity(position, codeLength, hammingCode);
        hammingCode[position - 1] = parityValue;
    }

    // Store the original hamming code
    for(i = 0; i < codeLength; i++) {
        originalCode[i] = hammingCode[i];
    }

    // Step 6: Output the calculated Hamming code
    printf("\nThe calculated Hamming Code is: ");
    for(i = 0; i < codeLength; i++) {
        printf("%d", hammingCode[i]);
    }
    printf("\n");

    // Step 7: Input the received Hamming code for error detection
    printf("Please enter the received Code Word:\n");
    for(i = 0; i < codeLength; i++) {
        scanf("%d", &hammingCode[i]);
    }

    // Step 8: Detect and locate errors
    int errorPosition = 0;
    for(i = 0; i < parityBitsCount; i++) {
        int position = (int)pow(2, i);
        int parityValue = calculateParity(position, codeLength, hammingCode);
        if(parityValue != 0) {
            errorPosition += position;
        }
    }

    // Step 9: Output whether there was an error and where it occurred
    if(errorPosition == 0) {
        // Additional check to compare received code with original code
        int differences = 0;
        for(i = 0; i < codeLength; i++) {
            if(hammingCode[i] != originalCode[i]) {
                differences++;
            }
        }
        if(differences == 0) {
            printf("The received Code Word is correct.\n");
        } else {
            printf("Multiple bit errors detected!\n");
        }
    } else {
        printf("Error detected at bit position: %d\n", errorPosition);
    }

    return 0;
}

// Modified function to take the code array as parameter
int calculateParity(int position, int codeLength, int code[]) {
    int count = 0, i, j;
    i = position - 1;
    while(i < codeLength) {
        for(j = i; j < i + position && j < codeLength; j++) {
            if(code[j] == 1)
                count++;
        }
        i = i + 2 * position;
    }
    return count % 2;
}
