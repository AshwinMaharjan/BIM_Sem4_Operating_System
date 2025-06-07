#include <stdio.h>
#include <stdlib.h>

void FCFS(int requests[], int n, int head) {
    int totalMovement = 0;

    printf("\n\nSequence of requests:\n");
    for (int i = 0; i < n; i++) {
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

    FCFS(requests, n, head);

    return 0;
}
