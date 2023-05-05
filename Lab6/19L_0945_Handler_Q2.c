#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PIPE_NAME "my_pipe"

int main()
{
    int fd;
    int send_array[5] = {1, 2, 3, 4, 5};
    int recv_array[1];

    // create named pipe
    mkfifo(PIPE_NAME, 0666);

    // open pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);

    // send array to calculator process
    write(fd, send_array, sizeof(send_array));

    // close pipe for writing
    close(fd);

    // open pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);

    // read result from calculator process
    read(fd, recv_array, sizeof(recv_array));

    // close pipe for reading
    close(fd);

    // display result
    printf("Sum of array is %d\n", recv_array[0]);

    // remove named pipe
    unlink(PIPE_NAME);

    return 0;
}

