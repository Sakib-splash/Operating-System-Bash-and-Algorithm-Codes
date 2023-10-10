//Shortest Job First (SJF) scheduling algorithm with preemption
#include <stdio.h>
#include <stdlib.h>

// Process structure
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
};

// Function to sort an array of processes based on burst time
void sortProcesses(struct Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    sortProcesses(processes, n);

    int currentTime = 0;
    int completed = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        int shortestIndex = -1;
        int shortestBurst = 999999;  // Some large value

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0 &&
                processes[i].burst_time < shortestBurst) {
                shortestIndex = i;
                shortestBurst = processes[i].burst_time;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        processes[shortestIndex].remaining_time--;
        printf("| P%d ", processes[shortestIndex].id);

        if (processes[shortestIndex].remaining_time == 0) {
            completed++;
            int turnaroundTime = currentTime - processes[shortestIndex].arrival_time + 1;
            int waitingTime = turnaroundTime - processes[shortestIndex].burst_time;
            totalTurnaroundTime += turnaroundTime;
            totalWaitingTime += waitingTime;
        }

        currentTime++;
    }

    printf("|\n\n");
    double averageWaitingTime = (double)totalWaitingTime / n;
    double averageTurnaroundTime = (double)totalTurnaroundTime / n;
    printf("Average Waiting Time: %.2lf\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2lf\n", averageTurnaroundTime);

    free(processes);

    return 0;
}
