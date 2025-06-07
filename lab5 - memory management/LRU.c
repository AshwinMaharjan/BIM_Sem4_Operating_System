#include <stdio.h>

#define FRAME_COUNT 3 // Number of frames in memory

// Function prototypes
void lruPageReplacement(int pages[], int pageCount);

int main() {
    // Example page reference stream
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    // Perform LRU page replacement
    lruPageReplacement(pages, pageCount);

    return 0;
}

void lruPageReplacement(int pages[], int pageCount) {
    int frame[FRAME_COUNT]; // Array to store the pages in memory frames
    int lastUsed[FRAME_COUNT]; // Array to store the last used time of each frame
    int pageFaults = 0; // Counter for page faults
    int time = 0; // Counter for time
    int i, j;
    int found;

    // Initialize frame and lastUsed arrays
    for (i = 0; i < FRAME_COUNT; i++) {
        frame[i] = -1; // Initialize frames to -1 (indicating empty)
        lastUsed[i] = -1; // Initialize last used times to -1
    }

    // Process each page in the page reference stream
    for (i = 0; i < pageCount; i++) {
        found = 0;

        // Check if the current page is already in one of the frames
        for (j = 0; j < FRAME_COUNT; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is found in the frame
                lastUsed[j] = time; // Update last used time
                break;
            }
        }

        // If page is not found in the frame, it is a page fault
        if (!found) {
            int lruIndex = 0;

            // Find the least recently used frame
            for (j = 1; j < FRAME_COUNT; j++) {
                if (lastUsed[j] < lastUsed[lruIndex]) {
                    lruIndex = j;
                }
            }

            // Replace the least recently used page
            frame[lruIndex] = pages[i];
            lastUsed[lruIndex] = time;
            pageFaults++;

            // Display the current state of the frames
            printf("Page fault for page %d: ", pages[i]);
            for (j = 0; j < FRAME_COUNT; j++) {
                if (frame[j] != -1) {
                    printf("%d ", frame[j]);
                }
            }
            printf("\n");
        }

        time++; // Increment the time counter for each page reference
    }

    // Display the total number of page faults
    printf("Total number of page faults: %d\n", pageFaults);
}
