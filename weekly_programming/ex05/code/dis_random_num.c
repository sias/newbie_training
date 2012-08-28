/*
file name:dis_random_num.c
purporse:get discordered random numbers and sent them to a file
creator:Bruse li
create time:2012-08-25
modify history:
Bruse li,2012-08-28
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 10000000
#define M 5000000
#define RAND_NUM rand()%N
int main()
{
	int i,code;
	int count=0;
	int *p;
	FILE *fp;
	if((fp=fopen("file.txt","w+"))==NULL)
	{
		printf("error on open!\n");
		exit(1);
	}
	if((p=(int*)malloc(M*sizeof(int))==NULL))
	{
		printf("malloc faild!\n");
		exit(1);
	}
	*p=RAND_NUM;
	while(count<M)
	{	
		code=RAND_NUM;
		for(i=0;i<=count;i++)
		{
			if((code-*(p+i))==0)
			{
				break;
			}
			if(i==count)
			{
				*(p+count)=code;
				fprintf(fp,"%5d",code);
				count++;
				break;
			}
		}
	}
	free(p);  
	fclose(fp);
}
