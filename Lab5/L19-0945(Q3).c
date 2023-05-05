#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int fd[2];
    pid_t pid;
    int filesize;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputfile> <outputfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Create output file
    int output_fd = creat(argv[2], 0644);
    if (output_fd == -1) {
        perror("creat");
        exit(EXIT_FAILURE);
    }

    // Create pipe
    if (pipe(fd) == -1) {
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
        close(fd[1]); // Close unused write end of pipe

        // Receive file size from parent
        read(fd[0], &filesize, sizeof(filesize));

        // Read data from pipe and write to output file
        int bytes_read;
        while ((bytes_read = read(fd[0], buffer, BUFFER_SIZE)) > 0) {
            write(output_fd, buffer, bytes_read);
        }

        // Clean up
        close(fd[0]);
        close(output_fd);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(fd[0]); // Close unused read end of pipe

        // Get file size
        off_t end_offset = lseek(input_fd, 0, SEEK_END);
        if (end_offset == -1) {
            perror("lseek");
            exit(EXIT_FAILURE);
        }
        filesize = end_offset;

        // Send file size to child
        write(fd[1], &filesize, sizeof(filesize));

        // Read data from input file and write to pipe
        lseek(input_fd, 0, SEEK_SET);
        int bytes_read;
        while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0) {
            write(fd[1], buffer, bytes_read);
        }

        // Clean up
        close(fd[1]);
        close(input_fd);
        exit(EXIT_SUCCESS);
    }
}

