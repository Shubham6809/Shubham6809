#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>  // For the sleep function

#define NUM_PHILOSOPHERS 5
#define THINKING 2
#define WAITING 1
#define EATING 0
#define LEFT (philosopher_num + 4) % NUM_PHILOSOPHERS
#define RIGHT (philosopher_num + 1) % NUM_PHILOSOPHERS

int philosopher_status[NUM_PHILOSOPHERS];
int philosopher_ids[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4};

sem_t status_mutex;
sem_t fork_sem[NUM_PHILOSOPHERS];

void assess_neighbors(int philosopher_num) {
    if (philosopher_status[philosopher_num] == WAITING &&
        philosopher_status[LEFT] != EATING &&
        philosopher_status[RIGHT] != EATING) {
        philosopher_status[philosopher_num] = EATING;
        sleep(2);
        printf("Philosopher %d picks up forks %d and %d\n", philosopher_num + 1, LEFT + 1, philosopher_num + 1);
        printf("Philosopher %d starts eating\n", philosopher_num + 1);
        sem_post(&fork_sem[philosopher_num]);
    }
}

void grab_forks(int philosopher_num) {
    sem_wait(&status_mutex);
    philosopher_status[philosopher_num] = WAITING;
    printf("Philosopher %d is hungry\n", philosopher_num + 1);
    assess_neighbors(philosopher_num);
    sem_post(&status_mutex);
    sem_wait(&fork_sem[philosopher_num]);
    sleep(1);
}

void release_forks(int philosopher_num) {
    sem_wait(&status_mutex);
    philosopher_status[philosopher_num] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", philosopher_num + 1, LEFT + 1, philosopher_num + 1);
    printf("Philosopher %d resumes thinking\n", philosopher_num + 1);
    assess_neighbors(LEFT);
    assess_neighbors(RIGHT);
    sem_post(&status_mutex);
}

void* philosopher_action(void* arg) {
    while (1) {
        int* phil_id = arg;
        sleep(1);
        grab_forks(*phil_id);
        sleep(0);
        release_forks(*phil_id);
    }
}

int main() {
    int i;
    pthread_t threads[NUM_PHILOSOPHERS];
    sem_init(&status_mutex, 0, 1);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) sem_init(&fork_sem[i], 0, 0);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher_action, &philosopher_ids[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) pthread_join(threads[i], NULL);
}
