#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

void findCompletionTime(struct Process proc[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        int highest_priority_index = -1;
        int highest_priority = 1000;
        for (int j = 0; j < n; j++) {
            if (proc[j].arrival_time <= current_time && proc[j].completion_time == 0 && proc[j].priority < highest_priority) {
                highest_priority = proc[j].priority;
                highest_priority_index = j;
            }
        }

        if (highest_priority_index == -1) {
            current_time++;
            i--;
            continue;
        }

        current_time += proc[highest_priority_index].burst_time;
        proc[highest_priority_index].completion_time = current_time;
        proc[highest_priority_index].turnaround_time = proc[highest_priority_index].completion_time - proc[highest_priority_index].arrival_time;
        proc[highest_priority_index].waiting_time = proc[highest_priority_index].turnaround_time - proc[highest_priority_index].burst_time;
    }
}

void printResults(struct Process proc[], int n) {
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n", proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
               proc[i].priority, proc[i].completion_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    int n = 4;
    struct Process proc[] = {{1, 0, 7, 3}, {2, 2, 7, 1}, {3, 3, 2, 4}, {4, 3, 2, 2}};

    findCompletionTime(proc, n);
    printResults(proc, n);

    return 0;
}