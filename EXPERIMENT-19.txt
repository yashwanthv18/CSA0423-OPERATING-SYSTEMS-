#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200 // Maximum number of cylinders on the disk

// Function to sort the disk request array in ascending order
void sort_requests(int requests[], int n) {
    // Using bubble sort for simplicity
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap requests[j] and requests[j+1]
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to simulate the C-SCAN disk scheduling algorithm
void cscan(int requests[], int n, int start) {
    int total_cylinders = MAX_CYLINDERS;
    int head_movement = 0;
    int current_position = start;

    // Sort requests in ascending order
    sort_requests(requests, n);

    // Move right (ascending order) from start position
    int i;
    for (i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            head_movement += abs(requests[i] - current_position);
            current_position = requests[i];
            printf("Servicing cylinder %d\n", current_position);
        }
    }

    // Move to the end of the disk
    head_movement += abs(total_cylinders - 1 - current_position);
    current_position = total_cylinders - 1;
    printf("Servicing cylinder %d\n", current_position);

    // Move left (ascending order) from cylinder 0 to start position
    head_movement += abs(0 - current_position);
    current_position = 0;
    printf("Servicing cylinder %d\n", current_position);

    // Move right (ascending order) from start position to remaining requests
    for (i = 0; i < n; i++) {
        if (requests[i] >= current_position) {
            head_movement += abs(requests[i] - current_position);
            current_position = requests[i];
            printf("Servicing cylinder %d\n", current_position);
        }
    }

    printf("Total head movement: %d cylinders\n", head_movement);
}

int main() {
    int requests[] = { 98, 183, 37, 122, 14, 124, 65, 67 };
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 53; // Starting position of disk arm

    printf("Disk Scheduling Algorithm: C-SCAN\n");
    printf("Initial position of disk arm: %d\n\n", start);

    cscan(requests, n, start);

    return 0;
}
