#include <stdio.h>

#define MAX_BLOCKS 10 // Define the maximum number of memory blocks
#define MAX_PROCESSES 10 // Define the maximum number of processes

// Function prototypes
void worstFit(int blocks[], int bSize, int processes[], int pSize);
void displayAllocation(int blocks[], int bSize, int processes[], int pSize, int allocation[]);

int main() {
    // Example memory blocks and processes
    int blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600}; // Memory blocks of different sizes
    int processes[MAX_PROCESSES] = {212, 417, 112, 426}; // Process memory requirements
    int blockSize = 5; // Number of memory blocks
    int processSize = 4; // Number of processes

    // Array to store the allocation status
    int allocation[MAX_PROCESSES];

    // Initialize allocation array
    for (int i = 0; i < processSize; i++) {
        allocation[i] = -1; // -1 indicates that the process is not allocated
    }

    // Perform Worst Fit allocation
    worstFit(blocks, blockSize, processes, processSize);

    return 0;
}

void worstFit(int blocks[], int bSize, int processes[], int pSize) {
    int allocation[MAX_PROCESSES]; // Array to store block allocation status

    // Initialize allocation array
    for (int i = 0; i < pSize; i++) {
        allocation[i] = -1;
    }

    // Allocate memory using Worst Fit strategy
    for (int i = 0; i < pSize; i++) {
        // Find the largest block that can accommodate the process
        int worstIdx = -1;
        for (int j = 0; j < bSize; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        // If a suitable block is found, allocate it
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blocks[worstIdx] -= processes[i]; // Decrease the size of the block
        }
    }

    // Display the allocation result
    displayAllocation(blocks, bSize, processes, pSize, allocation);
}

void displayAllocation(int blocks[], int bSize, int processes[], int pSize, int allocation[]) {
    printf("\n\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < pSize; i++) {
        printf("%d\t\t%d\t\t", i + 1, processes[i]);
        if (allocation[i] != -1) {
            printf("%d\t\t%d\n", allocation[i] + 1, blocks[allocation[i]]);
        } else {
            printf("Not Allocated\n");
        }
    }
}
