#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    // Create the shared memory segment
    key_t key = ftok("shared_memory_key", 1);
    int shm_id = shmget(key, SHM_SIZE, 0666);
    if (shm_id < 0) {
        printf("Error: could not create shared memory segment\n");
        exit(1);
    }

    // Attach to the shared memory segment
    char *shm_addr = shmat(shm_id, NULL, 0);
    if (shm_addr == (char *) -1) {
        printf("Error: could not attach to shared memory segment\n");
        exit(1);
    }

    // Read integers from shared memory and calculate the sum and average
    int total = 0;
    int count = 0;
    char *token = strtok(shm_addr, " ");
    while (strcmp(token, "END") != 0) {
        int num = atoi(token);
        total += num;
        count++;
        token = strtok(NULL, " ");
    }
    float average = (float) total / count;

    // Detach from the shared memory segment
    shmdt(shm_addr);

    // Delete the shared memory segment
    shmctl(shm_id, IPC_RMID, NULL);

    // Print the results
    printf("Sum: %d\n", total);
    printf("Average: %.2f\n", average);

    return 0;
}

