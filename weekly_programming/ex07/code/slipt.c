/*
file name:slipt.c
purpose:manage num
creator:Bruse li
create time:2012-09-8
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#define NUM_SIZE 10000
#define RANGE_NUM rand()%9999+1
int i=0;
int j;
int num[NUM_SIZE];
int swap(int a,int b)
{
	int temp;
	temp=a;
	a=b;
	b=temp;
}
void dif_num()
{
	srand((unsigned)time(NULL));
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=RANGE_NUM;
	}
}
void sam_num()
{
	int x;
	srand((unsigned)time(NULL));
	x=RANGE_NUM;
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=x;
	}
}
void inc_num()
{
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=i;	
	}
}
int split(int num[],int low,int high)
{
	int i=low+1;
	int j=high;
	int x=num[low];
	while(i<=j)
	{
		while(num[i]<=x)
		{
			i++;
		}
		while(num[j]>x)
		{
			j--;
		}
		if(i<j)
		{
		swap(num[i],num[j]);
		}
	}
	swap(num[low],num[j]);
	return j;
}
int quick_sort(int num[],int low,int high)
{
	int k;
	if(low<high)
	{
		k=split(num,low,high);
		quick_sort(num,low,k-1);
		quick_sort(num,k+1,high);
	}
	return 0;
}
void main()
{	
	clock_t begin1,end1,begin2,end2,begin3,end3;
	int num[NUM_SIZE];
	int high,low;
	low=0;
	high=NUM_SIZE-1;
	begin1=clock();
	dif_num();
	quik_sort(num,low,high);
	printf("dif_num range time:\n");
	for(i=0;i<NUM_SIZE;i++)
	{
		printf("%4d",num[i]);
	}
	end1=clock();
	printf("%lf second\n",(double)(end1-begin1)/CLOCKS_PER_SEC);
	begin2=clock();
	same_num();
	qiuk_sort(num,low,high);
	printf("same_num range time:\n");
	for(i=0;i<NUM_SIZE;i++)
	{	
		printf("%4d",num[i]);
	}
	end2=clock();
	printf("%lf second\n",(double)(end2-begin2)/CLOCKS_PER_SEC);
	begin3=clock();
	inc_Num();
	quick_sort(num,low,high);
	for(i=0;i<NUM_SIZE;i++)
	{
		printf("%4d",num[i]);
	}
	end3=clock();	
	printf("%lf second\n",(double)(end3-begin3)/CLOCKS_PER_SEC);
}
