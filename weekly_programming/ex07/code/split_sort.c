/*
file name split.c
porpurse:splot sort
creator:Bruse li
create time:2012-09-24
*/
#include<stdio.h>
#include<time.h>
#define NUM_SIZE 1000000
#define RANGE_NUM random()%NUM_SIZE
int i,j;
int cmp(const void *a,const void *b)
{
        return *(int*)a-*(int*)b;
}
void swap(int *a,int *b)
{
        int temp;
        temp=*a;
        *a=*b;
        *b=temp;
}
int sort(int n[],int begin)
{    
	int k;
	k=split(n,begin);
	qsort(n,k+1,sizeof(int),cmp);
        qsort(&n[k+1],NUM_SIZE-k-1,sizeof(int),cmp);
}
int split(int num[],int begin)
{
	int save[NUM_SIZE];
	int select;
	int x=num[0];
	for(i=0;i<NUM_SIZE;i++)
	{
		if(num[i]<=x)
		{
			save[j]=num[i];
			j++;
		}
	}
	swap(&save[0],&save[j-1]);
	select=j-1;
	for(i=1;i<NUM_SIZE;i++)
	{
		if(num[i]>x)
		{
			save[j]=num[i];
			j++;
		}
	}
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=save[i];
	}
	return select;
}
void dif_num(int get[])
{
        srand((unsigned)time(NULL));
        for(i=0;i<NUM_SIZE;i++)
        {
                get[i]=RANGE_NUM;
        }
}
void sam_num(int get[])
{
	int x;
	x=RANGE_NUM;
	for(i=0;i<NUM_SIZE;i++)
	{
		get[i]=x;
	}
}
int main()
{
	int begin=0;
	int rand[NUM_SIZE];
	FILE *fp;
	fp=fopen("file.txt","w+");
	if(fp<0)
	{
		printf("open error!\n");
	}
	clock_t start,end;
	//不同数排序
	dif_num(rand);
	start=clock();
	sort(rand,begin);
	for(i=0;i<NUM_SIZE;i++)
	{
		fprintf(fp,"%d ",rand[i]);
	}
	end=clock();
	printf("\ndif_num range time is: %lf second\n",(double)(end-begin)/CLOCKS_PER_SEC);
	fclose(fp);
}
