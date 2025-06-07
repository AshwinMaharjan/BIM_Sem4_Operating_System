#include <stdio.h>

#define N 4

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void FCFS(struct Process proc[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < proc[i].arrival_time)
            current_time = proc[i].arrival_time;
        proc[i].completion_time = current_time + proc[i].burst_time;
        current_time = proc[i].completion_time;
    }

    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("\n\nProcesses\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
	    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].turnaround_time, proc[i].waiting_time);
    }
}

int main() {
    struct Process proc[N] = {{0, 0, 7}, {1, 2, 7}, {2, 3, 2}, {3, 3, 2}};
    FCFS(proc, N);
    printProcesses(proc, N);
    return 0;
}
