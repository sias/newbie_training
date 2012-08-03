/*
filename:one.c
purpose:calculat how many ones in a num
creator:Bruse li
create time:2012-08-03
modify history:
Bruse li,2012-08-03
*/
#include<stdio.h>
/*计算一个整数中一的个数*/
int ones(int num)
{
	int count=0;
	while(num!=0)
	{
		if((num & 1)!=0)
		{
			count++;
		}
		num=(num>>1);
	}
	return count;
}
/*主函数*/
int main()
{
	int n;
	int code;
	int counter;
	printf("please enter a number:");
	scanf("%d",&n);
	code=n;
	counter=ones(n);//调用ones()函数
        printf("There are %d one in num %d \n",counter,code);   
  
   	return 0;
}
