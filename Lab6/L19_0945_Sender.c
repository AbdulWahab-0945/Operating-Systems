#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "myfifo"

int main()
{
    int fd;
    char operator, operand1[10], operand2[10];
    char buffer[100];

    printf("Enter operator and operands: ");
    scanf("%c %s %s", &operator, operand1, operand2);

    /* Create the FIFO if it does not exist */
    if (access(FIFO_NAME, F_OK) == -1)
    {
        mkfifo(FIFO_NAME, 0666);
    }

    /* Open the FIFO for writing */
    fd = open(FIFO_NAME, O_WRONLY);

    /* Write the data to the FIFO */
    sprintf(buffer, "%c %s %s", operator, operand1, operand2);
    write(fd, buffer, strlen(buffer)+1);

    /* Close the FIFO */
    close(fd);

    /* Open the FIFO for reading */
    fd = open(FIFO_NAME, O_RDONLY);

    /* Read the data from the FIFO */
    read(fd, buffer, 100);

    /* Close the FIFO */
    close(fd);

    /* Print the result */
    printf("Result: %s\n", buffer);

    return 0;
}

