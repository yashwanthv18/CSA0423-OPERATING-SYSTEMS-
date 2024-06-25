#u=include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared resource and synchronization structures
int shared_resource = 0;
sem_t mutex, wrt;
int read_count = 0;

// Reader function
void *reader(void *arg) {
    int reader_id = *(int *)arg;
    
    while (1) {
        // Entry section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt); // If this is the first reader, lock the resource for writers
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading: %d\n", reader_id, shared_resource);
        sleep(1); // Simulate reading

        // Exit section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // If this is the last reader, unlock the resource for writers
        }
        sem_post(&mutex);

        sleep(2); // Reader waiting before reading again
    }
    return NULL;
}

// Writer function
void *writer(void *arg) {
    int writer_id = *(int *)arg;
    
    while (1) {
        sem_wait(&wrt); // Lock the resource for writing
        shared_resource++;
        printf("Writer %d is writing: %d\n", writer_id, shared_resource);
        sleep(2); // Simulate writing
        sem_post(&wrt); // Unlock the resource after writing
        sleep(3); // Writer waiting before writing again
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // Mutex for mutual exclusion
    sem_init(&wrt, 0, 1);   // Semaphore for controlling write access

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Error creating reader thread");
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Error creating writer thread");
            return 1;
        }
    }

    // Wait for all threads to finish (which they won't)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
