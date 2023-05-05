#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;
int X1, Y1, Z1, W1, S1, S2, Z;

void *thread1(void *arg)
{
    sem_wait(&sem1);
    X1 = Z + 2;
    Y1 = Z1 * 5;
    S1 = X1 + Y1;
    printf("x=%d\n", S1);
    sem_post(&sem2);

    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    sem_wait(&sem2);
    Z1 = X1 * 2;
    W1 = Y1 + 5;
    S2 = Z1 + W1;
    printf("x=%d\n", S2);
    sem_post(&sem1);

    pthread_exit(NULL);
}

int main()
{
    printf("Enter a value for Z: ");
    scanf("%d", &Z);

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}

