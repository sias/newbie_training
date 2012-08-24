/*
file name:dif_num.c
purporse:copy the random numbers into a file
creator:Bruse li
create time:2012-08-25
*/
#include<stdio.h>
#include<stdio.h>
#include<fcntl.h>
#define N 10000000
#define K 5000000
int main()
{
	int fd,i,num;
	if(fd=open("/home/li/Desktop/h.txt",O_RDWR|O_APPEND)==-1)
	{
		printf("open file errno!\n");
	}
	srand((unsigned)time(NULL));
	for(i=0;i<K;i++)
	{
		num =rand()%N+1;
		printf("%d\n",num);
		if(write(fd,&num,sizeof(int))!=4)
		{
			printf("write errno!\n");
		}
	}
		close(fd);
}
