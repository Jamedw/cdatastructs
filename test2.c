#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void main(int argc,char* argv[])
{
    double time1 = (double)clock(),timedif;
    int max = 1000000,i;
    int array[max];
    for(i = 0;i<max;i++)
    {
    array[i] = i;
    }
  timedif = (((double) clock()) / CLOCKS_PER_SEC)-time1;
  printf("running time:%f\n",timedif);
 
return;
}

