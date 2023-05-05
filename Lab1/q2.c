 #include <stdio.h>
 #include <stdlib.h>
 
 
 int main(int argc,char *argv[]) 
  {
     int i,sum=0;
     float avg;
     
     if(argc<2) 
     { 
	printf("%s< no arguements provided\n",argv[0]);
	return 1; 
     }
     
      for (i = 1; i < argc; i++) {
    sum = sum+ atoi(argv[i]);
  }

  avg = (float) sum / (argc - 1);
  printf("Sum: %d\n", sum);
  printf("Average: %.2f\n", avg);

  return 0;
}



