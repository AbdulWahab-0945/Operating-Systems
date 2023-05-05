#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) 
    {
        printf("Usage: %s n\n", argv[0]);
        exit(1);
    }
    
    int n = atoi(argv[1]);
    
    if (n < 1) 
    {
        printf("Invalid value of n: %d\n", n);
        exit(1);
    }
    
    pid_t pid = fork();
    
    if (pid == 0)  // Child process
    {			 
    
        char arg1[10];  //this will take the N from the user to create a fibonacci series.
        
        sprintf(arg1, "%d", n);
        char *args[] = {"./Fib", arg1, NULL};
        execv(args[0], args);
        printf("Fibonacci Program not running.\n");
        exit(1);
    }
     
     else if (pid < 0) 
     { // Error
        printf("Process could not be forked\n");
        exit(1);
    }
     
    else 
    { // Parent process
        wait(NULL); // Wait for the child process to terminate
        printf("Child process terminated\n");
    }
    return 0;
}

