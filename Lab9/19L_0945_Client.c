#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: could not open input file\n");
        exit(1);
    }

    // Create the shared memory segment
    key_t key = ftok("shared_memory_key", 1);
    int shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
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

    // Read integers from the file and write them to shared memory
    char line[128];
    int total = 0;
    int count = 0;
    char *token = NULL;
    while (fgets(line, sizeof(line), input_file) != NULL) {
        token = strtok(line, " ");
        while (token != NULL) {
            int num = atoi(token);
            total += num;
            count++;
            sprintf(shm_addr, "%d ", num);
            shm_addr += strlen(shm_addr);
            token = strtok(NULL, " ");
        }
    }

    // Write a sentinel value to indicate the end of the data
    strcpy(shm_addr, "END");

    // Detach from the shared memory segment
    shmdt(shm_addr);

    // Close the input file
    fclose(input_file);

    return 0;
}

