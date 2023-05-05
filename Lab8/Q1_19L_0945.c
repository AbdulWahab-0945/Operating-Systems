#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void* worker(void* arg) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("Thread ID: %lu, Process ID: %d\n", tid, pid);
    return NULL;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

