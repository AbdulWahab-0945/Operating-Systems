#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int* fib_series;
    int length;
} fibonacci_result_t;

void* fibonacciGenerator(void* arg) {
    int n = *((int*) arg);
    int* fib_series = (int*) malloc((n+1) * sizeof(int));
    fib_series[0] = 0;
    fib_series[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib_series[i] = fib_series[i-1] + fib_series[i-2];
    }
    fibonacci_result_t* result = (fibonacci_result_t*) malloc(sizeof(fibonacci_result_t));
    result->fib_series = fib_series;
    result->length = n+1;
    pthread_exit(result);
}

void* countEvenNumbers(void* arg) {
    fibonacci_result_t* result = (fibonacci_result_t*) arg;
    int count = 0;
    for (int i = 0; i < result->length; i++) {
        if (result->fib_series[i] % 2 == 0) {
            count++;
        }
    }
    int* count_ptr = (int*) malloc(sizeof(int));
    *count_ptr = count;
    pthread_exit(count_ptr);
}

void* countOddNumbers(void* arg) {
    fibonacci_result_t* result = (fibonacci_result_t*) arg;
    int count = 0;
    for (int i = 0; i < result->length; i++) {
        if (result->fib_series[i] % 2 != 0) {
            count++;
        }
    }
    int* count_ptr = (int*) malloc(sizeof(int));
    *count_ptr = count;
    pthread_exit(count_ptr);
}

void* calculateSum(void* arg) {
    fibonacci_result_t* result = (fibonacci_result_t*) arg;
    int sum = 0;
    for (int i = 0; i < result->length; i++) {
        sum += result->fib_series[i];
    }
    FILE* fp = fopen("sum.txt", "w");
    fprintf(fp, "%d\n", sum);
    fclose(fp);
    int* sum_ptr = (int*) malloc(sizeof(int));
    *sum_ptr = sum;
    pthread_exit(sum_ptr);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Error: N must be a positive integer.\n");
        return 1;
    }
    pthread_t fib_thread, even_thread, odd_thread, sum_thread;
    fibonacci_result_t* fib_result;
    int* even_count, *odd_count, *sum;
    void* status;

    // Create and run the Fibonacci thread
    pthread_create(&fib_thread, NULL, fibonacciGenerator, (void*) &N);
    pthread_join(fib_thread, &status);
    fib_result = (fibonacci_result_t*) status;
    printf("ID = %ld, Series:", fib_thread);
    for (int i = 0; i < fib_result->length; i++) {
        printf(" %d", fib_result->fib_series[i]);
    }
    printf("\n");

    // Create and run the odd numbers counting thread
    pthread_create(&odd_thread, NULL, countOddNumbers, (void*) fib_result);
    pthread_join(odd_thread, &status);
    odd_count = (int*) status;
    printf("ID = %ld, Odd Numbers: %d\n", odd_thread, *odd_count);

    // Create and run the sum calculation thread  
    pthread_create(&sum_thread, NULL, calculateSum, (void*) fib_result);
    pthread_join(sum_thread, &status);
    sum = (int*) status;
    printf("ID = %ld, Sum: %d\n", sum_thread, *sum);

    // Free allocated memory
    free(fib_result->fib_series);
    free(fib_result);
    free(even_count);
    free(odd_count);
    free(sum);

    return 0;
    }

