#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ELEMENTS 5

int main() {
    int array[NUM_ELEMENTS] = {1, 5, 7, 2, 15};
    int sum;
    int fd1[2], fd2[2];
    pid_t pid;

    // Create pipes
    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(fd1[1]); // Close unused write end of first pipe
        close(fd2[0]); // Close unused read end of second pipe

        int recv_array[NUM_ELEMENTS];
        int size = sizeof(int) * NUM_ELEMENTS;

        // Receive array from parent
        read(fd1[0], recv_array, size);

        // Calculate sum
        sum = 0;
        for (int i = 0; i < NUM_ELEMENTS; i++) {
            sum += recv_array[i];
        }

        // Send sum back to parent
        write(fd2[1], &sum, sizeof(sum));

        // Clean up
        close(fd1[0]);
        close(fd2[1]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(fd1[0]); // Close unused read end of first pipe
        close(fd2[1]); // Close unused write end of second pipe

        int send_array[NUM_ELEMENTS];
        int size = sizeof(int) * NUM_ELEMENTS;

        // Send array to child
        write(fd1[1], array, size);

        // Receive sum from child
        read(fd2[0], &sum, sizeof(sum));

        // Display result
        printf("Sum recieved from child is:  %d\n", sum);

        // Clean up
        close(fd1[1]);
        close(fd2[0]);
        exit(EXIT_SUCCESS);
    }
}

