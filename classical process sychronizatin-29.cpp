#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int buffer_index = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = *((int *)arg);

    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[buffer_index] = item;
        buffer_index = (buffer_index + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;

    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[buffer_index - 1];
        buffer_index = (buffer_index - 1 + BUFFER_SIZE) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    pthread_exit(NULL);
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, &i);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}
