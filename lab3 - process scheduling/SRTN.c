#include <stdio.h>
#include <limits.h>

#define N 4

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void SRTN(struct Process proc[], int n) {
    int complete = 0, current_time = 0, min_remaining_time = INT_MAX, shortest = 0;
    int finish_time;
    int check = 0;

    while (complete != n) {
        for (int i = 0; i < n; i++) {
            if ((proc[i].arrival_time <= current_time) &&
                (proc[i].remaining_time < min_remaining_time) && proc[i].remaining_time > 0) {
                min_remaining_time = proc[i].remaining_time;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            current_time++;
            continue;
        }

        proc[shortest].remaining_time--;
        min_remaining_time = proc[shortest].remaining_time;
        if (min_remaining_time == 0)
            min_remaining_time = INT_MAX;

        if (proc[shortest].remaining_time == 0) {
            complete++;
            check = 0;
            finish_time = current_time + 1;
            proc[shortest].completion_time = finish_time;
        }
        current_time++;
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
    struct Process proc[N] = {{0, 0, 7, 7}, {1, 2, 7, 7}, {2, 3, 2, 2}, {3, 3, 2, 2}};
    SRTN(proc, N);
    printProcesses(proc, N);
    return 0;
}
