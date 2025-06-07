#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10

typedef struct {
    int page;
    bool referenceBit;
} Frame;

void printFrames(Frame frames[], int numFrames) {
    printf("Frames: ");
    for (int i = 0; i < numFrames; i++) {
        if (frames[i].page == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i].page);
        }
    }
    printf("\n");
}

int findPage(Frame frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i].page == page) {
            return i;
        }
    }
    return -1;
}

int findFrameToReplace(Frame frames[], int numFrames) {
    int pointer = 0;
    while (true) {
        if (!frames[pointer].referenceBit) {
            return pointer;
        }
        frames[pointer].referenceBit = false; // Reset the reference bit
        pointer = (pointer + 1) % numFrames;
    }
}

void secondChancePageReplacement(int pages[], int numPages, int numFrames) {
    Frame frames[MAX_FRAMES];
    int pageFaults = 0;

    // Initialize frames
    for (int i = 0; i < numFrames; i++) {
        frames[i].page = -1;
        frames[i].referenceBit = false;
    }

    for (int i = 0; i < numPages; i++) {
        int currentPage = pages[i];
        int frameIndex = findPage(frames, numFrames, currentPage);

        if (frameIndex == -1) { // Page fault
            int replaceIndex = findFrameToReplace(frames, numFrames);
            frames[replaceIndex].page = currentPage;
            frames[replaceIndex].referenceBit = true;
            pageFaults++;
        } else { // Page found
            frames[frameIndex].referenceBit = true; // Give it a second chance
        }

        printFrames(frames, numFrames);
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 2, 3, 2, 1, 4, 5, 2, 1, 2, 3, 4, 5};
    int numPages = sizeof(pages) / sizeof(pages[0]);
    int numFrames = 3;

    printf("\n\nPage Reference String: ");
    for (int i = 0; i < numPages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    secondChancePageReplacement(pages, numPages, numFrames);

    return 0;
}
