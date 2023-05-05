#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Process ID before execv: %d\n", getpid());     //this will provide the process id before using the execv command.
    
    char *args[] = {"./my_info", NULL};					   //file name is provided in the arguement, null is passed because execv expects command line instructions as second arguement in an array.
    execv(args[0], args);
    
    printf("Program doesn't enter myinfo.\n");
    return 0;
}

