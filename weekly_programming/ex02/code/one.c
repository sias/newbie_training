/*
filename:one.c
purpose:calculat how many ones in a num
creator:Bruse li
create time:2012-08-03
*/
#include<stdio.h>

int main(){

	int num;
	int count=0;
        printf("please enter a number:\n");
	scanf("%d",&num);
	int code=num;
        while(num!=0){
		if((num & 1) !=0){
			count++;
		}
		num=(num>>1);
        }
        printf("there are %d one in num %d \n",count,code);   
  
   	return 0;
}
