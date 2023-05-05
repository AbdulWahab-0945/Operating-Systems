#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    int status;
    pid_t pid;

    // Create Demo_Folder using mkdir command
    pid = fork();
    if (pid == 0)
     {
        execlp("mkdir", "mkdir", "Demo_Folder", NULL);
        exit(0);
    } 
    else 
    {
        wait(NULL);
    }

    // Create file1.txt and file2.txt in Demo_Folder using touch command
    
    pid = fork();
    
    if (pid == 0) 
    {
        chdir("Demo_Folder"); 		// this will change the directory to demo folder. Since the commands need to be executed in that folder.
       
        char *args[] = {"touch", "file1.txt", "file2.txt", NULL};
        execvp(args[0], args);
        exit(0);
    }
    
     else 
    {
        wait(NULL);
    }

    // List files in Demo_Folder using ls command
    pid = fork();
    if (pid == 0) 
    {
        chdir("Demo_Folder");
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        exit(0);
    } 
    
    else 
    {
        wait(NULL);
    }

    // Remove Demo_Folder using rm command
    pid = fork();
    if (pid == 0) 
    {
        char *args[] = {"rm", "-rf", "Demo_Folder", NULL};
        execvp(args[0], args);
        exit(0);
    }
     
     else 
     {
        wait(NULL);
     }

    return 0;
}





