#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

int main() 
{
    int fd[2];
    pid_t pid;
    pipe(fd);

    

    pid = fork();
    

    if (pid == 0)
     {
        // Child process
        close(fd[1]); // Close write end of pipe

        char buffer[1024];
        int nbytes = read(fd[0], buffer, sizeof(buffer));
        buffer[nbytes] = '\0';

        for (int i = 0; i < nbytes; i++) 
        {
            if (isupper(buffer[i]))			//isupper function checks if the alphabets are in upper case. 
            {
                buffer[i] = tolower(buffer[i]);		//converts the string into lower case if it was in upper case.
            }
             
            else if (islower(buffer[i])) 		//islower function checks if the alphabets are in lower case. 
            {
                buffer[i] = toupper(buffer[i]);		//converts the string into upper case if it was in lower case.
            }
        }

	 
        printf("Child process: %s\n", buffer);
        close(fd[0]); // Close read end of pipe
        exit(EXIT_SUCCESS);
    }
    
     else 
    {
        // Parent process
        printf("Parent process (PID=%d)\n", getpid());
	printf("Child process (PID=%d)\n", pid);
        close(fd[0]); // Close read end of pipe

        char message[] = "Hi There";
        int length = strlen(message);
        write(fd[1], message, length);
        printf("Parent process: %s\n", message);

        close(fd[1]); // Close write end of pipe
        wait(NULL); // Wait for child process to finish
        exit(EXIT_SUCCESS);
    }
}

