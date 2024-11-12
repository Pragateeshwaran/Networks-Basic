#include <stdio.h>

int sender(int arr[], int n) {
    int checksum, sum = 0;

    printf("\n****SENDER SIDE****\n");

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    printf("SUM IS: %d", sum);

    checksum = ~sum;  // 1's complement of sum
    printf("\nCHECKSUM IS: %d", checksum);

    return checksum;
}

void receiver(int arr[], int n, int sch) {
    int checksum, sum = 0;

    printf("\n\n****RECEIVER SIDE****\n");

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    printf("SUM IS: %d", sum);

    sum = sum + sch;
    checksum = ~sum;  // 1's complement of sum after adding sender's checksum

    printf("\nCHECKSUM AFTER ADDING SENDER'S CHECKSUM IS: %d", checksum);

    // Check if checksum is zero
    if (checksum == 0) {
        printf("\nNO ERROR DETECTED (CHECKSUM IS ZERO)\n");
    } else {
        printf("\nERROR DETECTED (CHECKSUM IS NOT ZERO)\n");
    }
}

int main() {
    int n, sch;

    printf("\nENTER SIZE OF THE STRING: ");
    scanf("%d", &n);

    int arr[n];

    printf("ENTER THE ELEMENTS OF THE ARRAY TO CALCULATE CHECKSUM:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sch = sender(arr, n);
    receiver(arr, n, sch);

    return 0;
}
