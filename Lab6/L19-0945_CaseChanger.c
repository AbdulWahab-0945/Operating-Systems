#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define PIPE_NAME "/tmp/my_pipe"

int main() {
    int fd;
    char message[100];
    char response[100];
    int i;

    // open the named pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // read the message from the named pipe
    read(fd, message, sizeof(message));

    // close the pipe
    close(fd);

    // reverse the case of each character in the message
    for (i = 0; i < strlen(message); i++) {
        if (isupper(message[i])) {
            response[i] = tolower(message[i]);
        } else if (islower(message[i])) {
            response[i] = toupper(message[i]);
        } else {
            response[i] = message[i];
        }
    }

    // open the named pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // write the response to the named pipe
    write(fd, response, strlen(response) + 1);

    return 0;
}

