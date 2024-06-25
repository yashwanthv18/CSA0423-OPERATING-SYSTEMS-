#include <stdio.h>

void fcfs(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n];

    // First process has 0 waiting time
    waiting_time[0] = 0;
    turnaround_time[0] = burst_time[0];

    // Calculate waiting and turnaround times for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    // Print execution order and turnaround times
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
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

    int processes[n], burst_time[n];

    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1; // Assuming process IDs start from 1
    }

    // Perform FCFS scheduling
    fcfs(processes, n, burst_time);

    return 0;
}

