#include <stdio.h>
#include <stdlib.h>

void LOOK(int requests[], int n, int head) {
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

    printf("\nSequence of requests:\n");

    // Move towards the lowest request first (downward)
    for (int i = 0; i < n; i++) {
        if (requests[i] > head) break;
        printf("%d -> ", requests[i]);
        totalMovement += abs(requests[i] - head);
        head = requests[i];
    }

    // After reaching the lowest request, move towards the highest request
    for (int i = n-1; i >= 0; i--) {
        if (requests[i] < head) break;
        printf("%d -> ", requests[i]);
        totalMovement += abs(requests[i] - head);
        head = requests[i];
    }

    printf("\nTotal Head Movement: %d\n", totalMovement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 53;

    LOOK(requests, n, head);

    return 0;
}
