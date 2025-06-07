#include <stdio.h>
#include <stdlib.h>

void CSCAN(int requests[], int n, int head, int diskSize) {
    int totalMovement = 0;

    // Sort the requests
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("\n\nSequence of requests:\n");

    // Move towards the end of the disk first (upward)
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) {
            printf("%d -> ", requests[i]);
            totalMovement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    // After reaching the end, move to the start of the disk (0)
    totalMovement += abs(diskSize - head - 1);
    head = 0;

    // Continue servicing the requests from the beginning of the disk
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) {
            printf("%d -> ", requests[i]);
            totalMovement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 53;
    int diskSize = 200;

    CSCAN(requests, n, head, diskSize);

    return 0;
}
