#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTITIONS 10

// Structure to represent a memory partition
struct memory_partition {
    int id;
    int size;
    int allocated;
};

struct memory_partition memory[MAX_PARTITIONS];

// Initialize memory partitions
void initialize_memory() {
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        memory[i].id = i + 1;
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

// Display memory partitions
void display_memory() {
    printf("Memory Partitions:\n");
    printf("------------------\n");
    printf("Partition ID\tSize\tAllocated\n");
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        printf("%d\t\t%d\t%s\n", memory[i].id, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
    printf("------------------\n");
}

// Worst Fit Allocation
void worst_fit_allocation(int process_id, int process_size) {
    int worst_fit_index = -1;
    int max_size = -1;

    // Find the largest partition that can accommodate the process
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size) {
            if (memory[i].size > max_size) {
                max_size = memory[i].size;
                worst_fit_index = i;
            }
        }
    }

    // Allocate memory if a suitable partition is found
    if (worst_fit_index != -1) {
        memory[worst_fit_index].allocated = 1;
        printf("Process %d allocated to Partition %d\n", process_id, memory[worst_fit_index].id);
    } else {
        printf("Unable to allocate memory for Process %d\n", process_id);
    }
}

// Deallocate memory for a process
void deallocate_memory(int process_id) {
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        if (memory[i].allocated && memory[i].id == process_id) {
            memory[i].allocated = 0;
            printf("Memory deallocated from Partition %d\n", memory[i].id);
            return;
        }
    }
    printf("Process %d not found or already deallocated\n", process_id);
}

int main() {
    initialize_memory();
    display_memory();

    // Example process allocations
    worst_fit_allocation(1, 50);
    worst_fit_allocation(2, 200);
    worst_fit_allocation(3, 100);
    worst_fit_allocation(4, 75);

    display_memory();

    // Deallocate a process
    deallocate_memory(2);
    display_memory();

    // Allocate another process after deallocation
    worst_fit_allocation(5, 150);
    display_memory();

    return 0;
}
