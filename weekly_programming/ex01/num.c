/*
file name:num.c
purpose:Ascending order
creator:Bruse
creat time:2012-07-27
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>
#include<time.h>

int cmp(const void *a,const void *b)
{
	return *(int*)a-*(int*)b;
}
int main()
{	
	clock_t begin,end;
	double cost;
	begin=clock();
        int n=pow(10,6);
        int num[n];
        int i,j;

	for(j=0;j<10;j++)
	  {
	   int *p=(int*)malloc(n*sizeof(int));
          
	   for(i=0;i<n;i++)
              num[i]=rand()%388780+100;
  	      qsort(num,n,sizeof(int),cmp);
	  
	    for(i=0;i<n;i++)
	     printf("%d\t",num[i]);
	   free(p);
          }

	end =clock();
	cost=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("%5.1lf seconds\n",cost);
	return 0;
				
}
