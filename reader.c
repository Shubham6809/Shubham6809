#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int read_count = 0;

sem_t empty, full;       // Semaphores for bounded buffer
sem_t rw_mutex;          // Semaphore for reader-writer synchronization
pthread_mutex_t mutex;   // Mutex for managing read_count

void* reader(void* arg) {
    int id = *((int *)arg);

    while (1) {
        sem_wait(&full);            // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock to update read_count

        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex);    // First reader locks the resource
        }
        pthread_mutex_unlock(&mutex); // Unlock after updating read_count

        // Reading section
        printf("Reader %d: Read item = %d from buffer[%d]\n", id, buffer[out], out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_lock(&mutex); // Lock to update read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex);    // Last reader unlocks the resource
        }
        pthread_mutex_unlock(&mutex); // Unlock after updating read_count

        sem_post(&empty);           // Signal an empty slot

        sleep(1); // Simulate delay
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int *)arg);

    while (1) {
        sem_wait(&empty); // Wait for an empty slot
        sem_wait(&rw_mutex); // Writer locks the resource

        // Writing section
        buffer[in] = (id) * 10; // Example write operation
        printf("Writer %d: Wrote item = %d to buffer[%d]\n", id, buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&rw_mutex); // Writer unlocks the resource
        sem_post(&full);     // Signal a full slot

        sleep(1); // Simulate delay
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&rw_mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (unreachable in this example)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;


}