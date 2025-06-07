#include <stdio.h>

#define FRAME_COUNT 3 // Number of frames in memory

// Function prototypes
void fifoPageReplacement(int pages[], int pageCount);

int main() {
    // Example page reference stream
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    // Perform FIFO page replacement
    fifoPageReplacement(pages, pageCount);

    return 0;
}

void fifoPageReplacement(int pages[], int pageCount) {
    int frame[FRAME_COUNT]; // Array to store the pages in memory frames
    int pageFaults = 0; // Counter for page faults
    int nextFrame = 0; // Index for the next frame to replace
    int i, j;
    int found;

    // Initialize frame array with -1 (indicating empty)
    for (i = 0; i < FRAME_COUNT; i++) {
        frame[i] = -1;
    }

    // Process each page in the page reference stream
    for (i = 0; i < pageCount; i++) {
        // Check if the current page is already in one of the frames
        found = 0;
        for (j = 0; j < FRAME_COUNT; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is found in the frame
                break;
            }
        }

        // If page is not found in the frame, it is a page fault
        if (!found) {
            frame[nextFrame] = pages[i]; // Replace the page in the next frame
            nextFrame = (nextFrame + 1) % FRAME_COUNT; // Move to the next frame
            pageFaults++; // Increment page fault count

            // Display the current state of the frames
            printf("Page fault for page %d: ", pages[i]);
            for (j = 0; j < FRAME_COUNT; j++) {
                if (frame[j] != -1) {
                    printf("%d ", frame[j]);
                }
            }
            printf("\n");
        }
    }

    // Display the total number of page faults
    printf("Total number of page faults: %d\n", pageFaults);
}
