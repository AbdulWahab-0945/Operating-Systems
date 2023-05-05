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
    int recv_array[5];
    int send_array[1];
    int sum = 0;
    int i;

    // open pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);

    // read array from handler process
    read(fd, recv_array, sizeof(recv_array));

    // close pipe for reading
    close(fd);

    // calculate sum
    for (i = 0; i < 5; i++) {
        sum += recv_array[i];
    }

    // open pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);

    // send sum to handler process
    send_array[0] = sum;
    write(fd, send_array, sizeof(send_array));

    // close pipe for writing
    close(fd);

    return 0;
}

