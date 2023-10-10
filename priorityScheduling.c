#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

struct GanttNode {
    int process_id;
    int start_time;
    int end_time;
    struct GanttNode *next;
};

void priority_scheduling(struct Process processes[], int n, struct GanttNode **gantt_chart) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int highest_priority = -1;
        int highest_priority_index = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0) {
                if (highest_priority == -1 || processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            current_time++;
        } else {
            struct Process *current_process = &processes[highest_priority_index];

            // Update Gantt Chart
            struct GanttNode *new_node = malloc(sizeof(struct GanttNode));
            new_node->process_id = current_process->id;
            new_node->start_time = current_time;
            new_node->end_time = current_time + 1;
            new_node->next = NULL;

            if (*gantt_chart == NULL) {
                *gantt_chart = new_node;
            } else {
                struct GanttNode *temp = *gantt_chart;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = new_node;
            }

            current_process->burst_time--;
            current_time++;

            if (current_process->burst_time == 0) {
                current_process->turnaround_time = current_time - current_process->arrival_time;
                completed++;
            }
        }
    }
}

void print_gantt_chart(struct GanttNode *gantt_chart) {
    printf("\nGantt Chart:\n");
    while (gantt_chart != NULL) {
        printf("| P%d ", gantt_chart->process_id);
        gantt_chart = gantt_chart->next;
    }
    printf("|\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].id = i + 1;
        printf("   Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("   Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("   Priority: ");
        scanf("%d", &processes[i].priority);
    }

    struct GanttNode *gantt_chart = NULL;
    priority_scheduling(processes, n, &gantt_chart);

    print_gantt_chart(gantt_chart);

    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    printf("\nProcess\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;

        printf("%d\t%d\t\t%d\n", processes[i].id, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    // Free allocated memory
    free(processes);
    while (gantt_chart != NULL) {
        struct GanttNode *temp = gantt_chart;
        gantt_chart = gantt_chart->next;
        free(temp);
    }

    return 0;
}


