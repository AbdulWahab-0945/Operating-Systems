#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function to compute the summation of integers from 0 to N
int summation(int N) {
    int sum = 0;
    for (int i = 0; i <= N; i++) {
        sum += i;
    }
    return sum;
}

// Thread function to perform the summation of N
void *worker(void *arg) {
    int N = *((int*) arg);
    int sum = summation(N);
    printf("The summation of integers from 0 to %d is: %d\n", N, sum);
    pthread_exit(NULL);
}

// Main function to create a thread and perform the summation of N
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    pthread_t thread;
    pthread_create(&thread, NULL, worker, &N);
    pthread_join(thread, NULL);

    return 0;
}

