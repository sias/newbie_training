/*
file name:manege_num.c
purporse:range the numbers
creator:Bruse li
create time:2012-08-30
*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define SHIFT 5
#define MASK 0x1F
#define bit 32
//#define N 10000000
//#define K 5000000
#define N 1000
#define K 100
#define LEN N*sizeof(int)
int main()
{
	int a[1+N/bit];
	int i,num;
	FILE *fp;
	//int *p;
	//p=(int*)malloc(N*sizeof(int));
	/*if(p==NULL)
	{
		printf("malloc errorn\n");
		exit(1);
	}*/
	fp=fopen("file.txt","r");
	if(fp==NULL)
	{
		printf("open file fail!\n");
		exit(1);
	}
	for(i=0;i<N;i++)
	{
		a[i>>SHIFT]|=~(1<<(i&MASK));
		//*(p+i)=0;
	}
	for(i=0;i<K;i++)
	{
		fscanf(fp,"%d ",&num);
		a[i>>SHIFT]|=(1<<(i&MASK));
		//*(p+num)=1;
	}
	for(i=0;i<N;i++)
	{
		//while(*(p+i))
		while(a[i>>SHIFT])
		{
			printf("....%d....\n",i);
			break;
		}	
	}
	//free(p);
	fclose(fp);
}
