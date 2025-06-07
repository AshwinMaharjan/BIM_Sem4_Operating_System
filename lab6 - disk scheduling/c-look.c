#include <stdio.h>
#include <stdlib.h>

void C_LOOK(int requests[], int n, int head) {
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

    // Find the starting point
    int startIndex;
    for (startIndex = 0; startIndex < n; startIndex++) {
        if (requests[startIndex] >= head) {
            break;
        }
    }

    // Serve the requests in circular order
    for (int i = startIndex; i < n; i++) {
        printf("%d -> ", requests[i]);
        totalMovement += abs(requests[i] - head);
        head = requests[i];
    }

    // Continue to the beginning of the request list
    for (int i = 0; i < startIndex; i++) {
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

    C_LOOK(requests, n, head);

    return 0;
}
