#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void sort(int array[],bool order)
  {
  	int size=sizeof(array) / sizeof(int);
  	int temp;
  	
  	  	for (int i=0; i < size -1; i++)
  	{
		for (int j=0;j<size-i-1;j++)
		{
			if((order==1 && array[j] > array[j+1]) || (order == 0 && array[j]<array[j+1]))
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
				
		}		  


  	}

  }
  
  
  void findHighest(int array[],int nth)
  {
  	int i=0;
  	if (array[i] > array[i+1])
  	{
  		printf("%d",array[nth]);
  	}
  	
  	else 
  	{
  		int size= sizeof(array)/sizeof(int);
  		nth=size-nth;
  		
  		printf("%d\n",array[nth]);
  	}
  	
  	
  	
  }
  
  void print(int array[])
  {
    int size= sizeof(array)/sizeof(int);
    
    for (int i=0;i<size;i++)
    {
    	printf("%d",array[i]);
    }
  }
