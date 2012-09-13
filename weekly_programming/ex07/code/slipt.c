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
#define RANGE_NUM rand()%10000
int i=0;
int x;
void swap(int *a,int *b)
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void dif_num(int num[])
{
	srand((unsigned)time(NULL));
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=RANGE_NUM;
	}
}
void sam_num(int num[])
{
	srand((unsigned)time(NULL));
	x=RANGE_NUM;
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=x;
	}
}
void inc_num(int num[])
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
			swap(&num[i],&num[j]);
		}
	}
	swap(&num[low],&num[j]);
	return j;
}
int quick_sort(int n[],int low,int high)
{
	int k;
	if(low<high)
	{
		k=split(n,low,high);
		quick_sort(n,low,k-1);
		quick_sort(n,k+1,high);
	}
	return 0;
}
void main()
{	
	FILE *fp1,*fp2,*fp3;
	clock_t begin1,end1,begin2,end2,begin3,end3;
	int n[NUM_SIZE];
	int high,low;
	low=0;
	high=NUM_SIZE-1;
	fp1=fopen("dif.txt","w+");
	fp2=fopen("sam.txt","w+");
	fp3=fopen("inc.txt","w+");
	//range difrent numbers 
	begin1=clock();
	dif_num(n);
	quick_sort(n,low,high);
	for(i=0;i<NUM_SIZE;i++)
	{
		fprintf(fp1,"%d ",n[i]);
	}
	end1=clock();
	printf("\ndif_num range time is: %lf second\n",(double)(end1-begin1)/CLOCKS_PER_SEC);
	//range same number
	begin2=clock();
	sam_num(n);
	quick_sort(n,low,high);
	for(i=0;i<NUM_SIZE;i++)
	{	
		fprintf(fp2,"%d ",n[i]);
	}
	end2=clock();
	printf("\nsam_num range time is: %lf second\n",(double)(end2-begin2)/CLOCKS_PER_SEC);
	//range increas number
	begin3=clock();
	inc_num(n);
	quick_sort(n,low,high);
	for(i=0;i<NUM_SIZE;i++)
	{
		fprintf(fp3,"%d ",n[i]);
	}
	end3=clock();	
	printf("\ninc_num range time is: %lf second\n",(double)(end3-begin3)/CLOCKS_PER_SEC);	
}
