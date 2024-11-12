#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WINDOW_SIZE 4
#define BUFFER_SIZE 20

// Selective Repeat
void selective_repeat() {
    int sender_buffer[BUFFER_SIZE] = {0};
    bool ack[BUFFER_SIZE] = {false};
    int base = 0;
    int next_seq_num = 0;

    printf("Selective Repeat Protocol\n");

    while (base < BUFFER_SIZE) {
        // Send packets
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < BUFFER_SIZE) {
            printf("Sending packet %d\n", next_seq_num);
            sender_buffer[next_seq_num] = next_seq_num;
            next_seq_num++;
        }

        // Simulate random ACKs
        for (int i = base; i < next_seq_num; i++) {
            if (rand() % 2 == 0 && !ack[i]) {
                printf("ACK received for packet %d\n", i);
                ack[i] = true;
            }
        }

        // Move base
        while (ack[base] && base < BUFFER_SIZE) {
            base++;
        }
    }
}

// Go-Back-N
void go_back_n() {
    int sender_buffer[BUFFER_SIZE] = {0};
    int base = 0;
    int next_seq_num = 0;

    printf("\nGo-Back-N Protocol\n");

    while (base < BUFFER_SIZE) {
        // Send packets
        while (next_seq_num < base + WINDOW_SIZE && next_seq_num < BUFFER_SIZE) {
            printf("Sending packet %d\n", next_seq_num);
            sender_buffer[next_seq_num] = next_seq_num;
            next_seq_num++;
        }

        // Simulate ACK (only for the base packet)
        if (rand() % 2 == 0) {
            printf("ACK received for packet %d\n", base);
            base++;
        } else {
            printf("Timeout for packet %d, resending window\n", base);
            next_seq_num = base;
        }
    }
}

int main() {
    selective_repeat();
    go_back_n();
    return 0;
}
