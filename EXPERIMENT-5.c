#include <stdio.h>
#include <stdlib.h>

// Structure to hold process information
struct Process {
    int process_id;
    int burst_time;
    int priority;
};

// Function to perform Priority Scheduling
void priority_scheduling(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    // Sort processes based on priority (higher priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority < processes[j + 1].priority) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate waiting and turnaround times
    waiting_time[0] = 0;
    turnaround_time[0] = processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }

    // Print execution order and turnaround times
    printf("Process\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time,
               processes[i].priority, waiting_time[i], turnaround_time[i]);
    }

    // Calculate average turnaround time
    float avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_turnaround_time += turnaround_time[i];
    }
    avg_turnaround_time /= n;

    printf("\nAverage Turnaround Time = %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst times and priorities for each process
    printf("Enter burst times and priorities for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].process_id = i + 1; // Assuming process IDs start from 1
    }

    // Perform Priority Scheduling
    priority_scheduling(processes, n);

    return 0;
}

