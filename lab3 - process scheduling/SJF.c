#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;         // Process ID
    int arrivalTime; // Arrival time of the process
    int burstTime;   // Burst time of the process
    int completionTime; // Completion time of the process
    int waitingTime; // Waiting time of the process
    int turnAroundTime; // Turnaround time of the process
};

void sortProcessesByArrivalAndBurst(struct Process p[], int n) {
    // Sort by arrival time first, then by burst time if arrival times are the same
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrivalTime > p[j + 1].arrivalTime || 
                (p[j].arrivalTime == p[j + 1].arrivalTime && p[j].burstTime > p[j + 1].burstTime)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateCompletionTimes(struct Process p[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }
        p[i].completionTime = currentTime + p[i].burstTime;
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnAroundTime - p[i].burstTime;
        currentTime = p[i].completionTime;
    }
}

void printProcessDetails(struct Process p[], int n) {
    printf("\n\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }
}

int main() {
    struct Process processes[] = {
        {0, 0, 7},
        {1, 2, 7},
        {2, 3, 2},
        {3, 3, 2}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    
    // Sort processes based on arrival time and burst time
    sortProcessesByArrivalAndBurst(processes, n);
    
    // Calculate completion, waiting, and turnaround times
    calculateCompletionTimes(processes, n);
    
    // Print the process details
    printProcessDetails(processes, n);
    
    return 0;
}
