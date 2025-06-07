#include <stdio.h>
#include <limits.h>

#define FRAME_COUNT 3 // Number of frames in memory

// Function prototypes
void optimalPageReplacement(int pages[], int pageCount);

int main() {
    // Example page reference stream
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int pageCount = sizeof(pages) / sizeof(pages[0]);

    // Perform Optimal Page Replacement
    optimalPageReplacement(pages, pageCount);

    return 0;
}

void optimalPageReplacement(int pages[], int pageCount) {
    int frame[FRAME_COUNT]; // Array to store the pages in memory frames
    int pageFaults = 0; // Counter for page faults
    int i, j, k;
    int farthest, index, temp;

    // Initialize frame array with -1 (indicating empty)
    for (i = 0; i < FRAME_COUNT; i++) {
        frame[i] = -1;
    }

    // Process each page in the page reference stream
    for (i = 0; i < pageCount; i++) {
        // Check if the current page is already in one of the frames
        int found = 0;
        for (j = 0; j < FRAME_COUNT; j++) {
            if (frame[j] == pages[i]) {
                found = 1; // Page is found in the frame
                break;
            }
        }

        // If the page is not found in the frame, it is a page fault
        if (!found) {
            // Check for an empty frame
            int emptyFrame = -1;
            for (j = 0; j < FRAME_COUNT; j++) {
                if (frame[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            // If an empty frame is found, use it
            if (emptyFrame != -1) {
                frame[emptyFrame] = pages[i];
            } else {
                // Find the page that will not be used for the longest time
                farthest = INT_MIN;
                for (j = 0; j < FRAME_COUNT; j++) {
                    int k;
                    for (k = i + 1; k < pageCount; k++) {
                        if (frame[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                index = j;
                            }
                            break;
                        }
                    }
                    if (k == pageCount) { // Page not found in future references
                        index = j;
                        break;
                    }
                }
                frame[index] = pages[i];
            }

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
