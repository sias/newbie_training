/*
file name:insert_sort.c
porpurse:sort  nums
creator:Bruse li
create time:2012-08-16
modify time:
Bruse li,2012-08-17
*/
#include<stdio.h>
#include<math.h>
#include<time.h>
#define NUM_SIZE 100000
#define RANGE_NUM rand()%99999+1
int i;
int num[NUM_SIZE];
//获得10万个随机数
void dif_num()
{
	srand((unsigned)time(NULL));
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=RANGE_NUM;
	}
}
//获得10万个相同随机数
void sam_num()
{
	int x;
	srand((unsigned)time(NULL))
	x=RANGE_NUM;
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=x;
	}
}
//获得10万个递增随机数
void inc_num()
{
	for(i=0;i<NUM_SIZE;i++)
	{
		num[i]=i;	
	}
}
//打印排序后的100个数
void print()
{
	for(i=0;i<NUM_SIZE;i++)
	{
		printf("%d\n",num[i]);
	}

}
int main()
{
	clock_t begin,end;
	int j,temp,choose;
	printf("please make your choose:\n(1):产生10万随机数.\n(2):产生十万相同随机数.\n(3):产生十万递增数\n:");
        scanf("%d",&choose);
	switch(choose)
	{
	case 1:
		dif_num();
		break;
	case 2:
		sam_num();
		break;
	case 3:
		inc_num();
		break;
	default:
		printf("error choice!\n");
	}
	begin=clock();
	for(i=0;i<NUM_SIZE;i++)
	{	
		temp=num[i];
		for(j=i;(j>0)&&(temp<num[j-1]);j--)
		{
			num[j]=num[j-1];
		}
		num[j]=temp;
	}
	end=clock();
	print();
	printf("%lf  second\n",(double)(end-begin)/CLOCKS_PER_SEC);
	return 0;
}
