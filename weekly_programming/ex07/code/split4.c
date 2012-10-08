/*
file name: split4.c
purporse: sort split
creator: Bruse li
create time:2012-09-28
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM_SIZE 100000
int split(int num[],int begin,int right)
{
	int i;
	int j;
	int x;
	int temp;
	x=num[begin];
	//从右到左一次比较
	for(i=right-1;i>=begin;i--)
	{	
		if(num[i]<x)
		{
			temp=num[i];
			for(j=i;j>=begin;j--)
			{
				num[j]=num[j-1];
			}
			num[begin]=temp;//把小的数放在选中数移动的位置
			begin++;//选中数的位置右移一位
			i++;//返回当前最右端的位置。（比较的那个数的位置已经被替换）
		}
	}
	return begin;//分点的位置
}
int sort(int sort_num[],int begin,int right)
{
	int p;
	int k=0;
	int point;
	while(begin<right)
	{
		p=split(sort_num,begin,right);
		begin=0;//从最左边0节点开始分
		begin=k;
		if(p==begin||p==begin+1)//如过返回节点等起始节点，起始节点右移。
		{
			k++;
		}
	}
}
int main()
{
	int p;
	int begin=0;
	FILE *fp;
	clock_t start,end;
	int right=NUM_SIZE;
	int rand[NUM_SIZE];
	fp=fopen("split.txt","w++");
	if(fp==NULL)
	{
		fprintf(stderr,"Open file error!\n");
		exit(1);
	}
	for(p=0;p<NUM_SIZE;p++)
	{
		rand[p]=random()%99999; 
        }
	start=clock();
	sort(rand,begin,right);
	end=clock();
	printf("spent %lf secends\n",(double)(end-start)/CLOCKS_PER_SEC);
	for(p=0;p<NUM_SIZE;p++)
	{
		fprintf(fp," *%d* ",rand[p]);
	}
	fclose(fp);
}

