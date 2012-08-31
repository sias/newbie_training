/*
file name:manege_num.c
purporse:range the numbers
creator:Bruse li
create time:2012-08-30
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define N 10000000
#define K 5000000
#define LEN N*sizeof(int)
int main()
{
	int i,num;
	FILE *fp;
	int *p;
	p=(int*)malloc(N*sizeof(int));
	if(p==NULL)
	{
		printf("malloc errorn\n");
		exit(1);
	}
	fp=fopen("file.txt","r");
	if(fp==NULL)
	{
		printf("open file fail!\n");
		exit(1);
	}
	for(i=0;i<N;i++)
	{
		*(p+i)=0;
	}
	for(i=0;i<K;i++)
	{
		fscanf(fp,"%d ",&num);
		*(p+num)=1;
	}
	for(i=0;i<N;i++)
	{
		while(*(p+i))
		{
			printf("....%d....\n",i);
			break;
		}	
	}
	free(p);
	fclose(fp);
}
