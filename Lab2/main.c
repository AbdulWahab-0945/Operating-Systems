#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "header.h"


int main( int argc, char *argv[])
{
   int arrsize=argc-2;
   int array[arrsize];
   int order= atoi (argv[argc-2]);
   bool nth = atoi(argv[argc - 1]);



    sort(array, order);
    //print(array);
    findHighest(array, nth);
   
   	
}
