/*
file name:insert_sort.c
porpurse:sort  nums
creator:Bruse li
create time:2012-08-16
*/
#include<stdio.h>
#include<math.h>
#include<time.h>
int main()
{
	int i,j,temp;
	int choose;
	int num[99999];
	printf("please make your choose:\n(1):产生10万随机数.\n(2):产生十万相同随机数.\n(3):产生十万递增数\n:");
	scanf("%d",&choose);
	switch(choose)
	/*产生十万个随机数*/
	{
	case 1:
		srand((unsigned)time(NULL));
		for(i=0;i<100000;i++)
		{
			num[i]=rand()%99999+1;	
		}
		break;
		//产生十万个相同随机数
	case 2:
		for(i=0;i<100000;i++)
		{
			srand((unsigned)time(NULL));
			num[i]=rand()%99999+1;
		}
		break;
	case 3:
		//产生十万个递增数
		for(i=0;i<100000;i++)
		{
			num[i]=i;
		}
		break;
	default:
		printf("error choice!\n");
	return 0;
	}
	//插入排序
	for(i=1;i<10000;i++)
	{
		temp=num[i];
		for(j=i;(j>0)&&(temp<num[j-1]);j--)
		{
			num[j]=num[j-1];
		}
	num[j]=temp;
	}
	for(i=0;i<1000;i++)
	printf("%d\n",num[i]);
}
