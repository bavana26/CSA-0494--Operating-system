#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by each thread
void *thread_function(void *arg) {
    int thread_id = *(int *)arg;
    printf("Thread %d is running\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[5]; // Array to hold thread IDs
    int thread_args[5];   // Array to hold thread arguments

    // Create and run five threads
    for (int i = 0; i < 5; ++i) {
        thread_args[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished\n");

    return 0;
}
