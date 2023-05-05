#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int input_fd, output_fd, n;
    char buffer[500];

    // Check command-line arguments
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        exit(1);
    }

    // Open input file for reading
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        printf("Error opening input file\n");
        exit(1);
    }

    // Open output file for writing
    output_fd = open(argv[2], O_WRONLY | O_CREAT,0644 );
    if (output_fd == -1) {
        printf("Error opening output file\n");
        exit(1);
    }

    // Redirect input and output
    dup2(input_fd, STDIN_FILENO);
    dup2(output_fd, STDOUT_FILENO);

    // Read from input and write to output
    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        printf("%.*s", n, buffer);
    }

    // Close files and exit
    close(input_fd);
    close(output_fd);
    return 0;
}

