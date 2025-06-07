#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int findClosest(int requests[], bool processed[], int n, int head) {
    int minDistance = 9999;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (!processed[i] && abs(requests[i] - head) < minDistance) {
            minDistance = abs(requests[i] - head);
            index = i;
        }
    }
    return index;
}

void SSTF(int requests[], int n, int head) {
    bool processed[n];
    for (int i = 0; i < n; i++) processed[i] = false;

    int totalMovement = 0;

    printf("\n\nSequence of requests:\n");
    for (int i = 0; i < n; i++) {
        int index = findClosest(requests, processed, n, head);
        processed[index] = true;
        printf("%d -> ", requests[index]);
        totalMovement += abs(requests[index] - head);
        head = requests[index];
    }
    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 53;

    SSTF(requests, n, head);

    return 0;
}
