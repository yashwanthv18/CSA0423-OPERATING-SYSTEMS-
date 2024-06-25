#include <stdio.h>

// Structure to hold process information
struct Process {
    int process_id;
    int burst_time;
    int remaining_time;
};

// Function to perform Round Robin scheduling
void round_robin(struct Process processes[], int n, int time_quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int waiting_time[n], turnaround_time[n];
    int completed = 0;

    // Initialize remaining_time and waiting_time
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        waiting_time[i] = 0;
    }

    // Simulate Round Robin scheduling
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time <= time_quantum) {
                    // Process completes within time quantum
                    current_time += processes[i].remaining_time;
                    turnaround_time[i] = current_time;
                    processes[i].remaining_time = 0;
                    completed++;
                } else {
                    // Process still needs more time
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }
            }
        }
    }

    // Calculate waiting times
    for (int i = 0; i < n; i++) {
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
    }

    // Print execution order and turnaround times
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time,
               waiting_time[i], turnaround_time[i]);
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
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input burst times for each process
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1; // Assuming process IDs start from 1
    }

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    // Perform Round Robin scheduling
    round_robin(processes, n, time_quantum);

    return 0;
}

