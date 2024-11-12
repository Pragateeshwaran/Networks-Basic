#include <stdio.h>
#include <string.h>

void calculate_CRC(char data[], char divisor[], char crc[]) {
    int data_len = strlen(data);
    int divisor_len = strlen(divisor);

    char temp[data_len + divisor_len];
    strcpy(temp, data);

    // Append n-1 zeros to data where n is divisor length
    for (int i = 0; i < divisor_len - 1; i++) {
        temp[data_len + i] = '0';
    }
    temp[data_len + divisor_len - 1] = '\0';

    // Binary division
    for (int i = 0; i < data_len; i++) {
        if (temp[i] == '1') {
            for (int j = 0; j < divisor_len; j++) {
                temp[i + j] = (temp[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    // Remainder is the CRC
    strncpy(crc, &temp[data_len], divisor_len - 1);
    crc[divisor_len - 1] = '\0';
}

int main() {
    char data[] = "11100";
    char divisor[] = "1001";
    char crc[4];

    calculate_CRC(data, divisor, crc);
    printf("CRC: %s\n", crc);

    return 0;
}
