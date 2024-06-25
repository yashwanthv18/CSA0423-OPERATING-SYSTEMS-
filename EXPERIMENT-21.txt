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

// First Fit Allocation
void first_fit_allocation(int process_id, int process_size) {
    // Find the first partition that can accommodate the process
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size) {
            memory[i].allocated = 1;
            printf("Process %d allocated to Partition %d\n", process_id, memory[i].id);

            // Split the partition if there's leftover space
            if (memory[i].size > process_size) {
                struct memory_partition new_partition;
                new_partition.id = memory[i].id + 1; // New partition ID
                new_partition.size = memory[i].size - process_size;
                new_partition.allocated = 0;

                // Shift partitions to make space for the new one
                for (int j = MAX_PARTITIONS - 1; j > i; j--) {
                    memory[j] = memory[j - 1];
                }

                memory[i + 1] = new_partition;
                memory[i].size = process_size; // Resize the original partition
            }

            return;
        }
    }

    printf("Unable to allocate memory for Process %d\n", process_id);
}

// Deallocate memory for a process
void deallocate_memory(int process_id) {
    for (int i = 0; i < MAX_PARTITIONS; i++) {
        if (memory[i].allocated && memory[i].id == process_id) {
            memory[i].allocated = 0;
            printf("Memory deallocated from Partition %d\n", memory[i].id);

            // Merge adjacent free partitions if possible
            if (i < MAX_PARTITIONS - 1 && !memory[i + 1].allocated) {
                memory[i].size += memory[i + 1].size;
                // Shift partitions to fill the gap
                for (int j = i + 1; j < MAX_PARTITIONS - 1; j++) {
                    memory[j] = memory[j + 1];
                }
                memory[MAX_PARTITIONS - 1].size = 0;
                memory[MAX_PARTITIONS - 1].allocated = 0;
            }
            return;
        }
    }
    printf("Process %d not found or already deallocated\n", process_id);
}

int main() {
    initialize_memory();
    display_memory();

    // Example process allocations
    first_fit_allocation(1, 50);
    first_fit_allocation(2, 200);
    first_fit_allocation(3, 100);
    first_fit_allocation(4, 75);

    display_memory();

    // Deallocate a process
    deallocate_memory(2);
    display_memory();

    // Allocate another process after deallocation
    first_fit_allocation(5, 150);
    display_memory();

    return 0;
}
