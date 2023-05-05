#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PIPE_NAME "/tmp/my_pipe"
#define MAX_BUF 1024

int main() {
    int fd1, fd2;
    char message[MAX_BUF];
    char response[MAX_BUF];

    // create the named pipes if they don't exist
    if (mkfifo(PIPE_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // open the named pipe for writing
    fd1 = open(PIPE_NAME, O_WRONLY);
    if (fd1 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // get input from user
    printf("Enter a message to send: ");
    fgets(message, MAX_BUF, stdin);

    // write the message to the named pipe
    write(fd1, message, strlen(message) + 1);

    // close the write end of the named pipe
    close(fd1);

    // open the named pipe for reading
    fd2 = open(PIPE_NAME, O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // read the response from the named pipe
    read(fd2, response, sizeof(response));

    // print the modified message
    printf("Modified message: %s", response);

    // close the read end of the named pipe
    close(fd2);

    // remove the named pipe
    unlink(PIPE_NAME);

    return 0;
}

