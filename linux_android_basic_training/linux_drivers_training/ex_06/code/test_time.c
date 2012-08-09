/*
file name:test_timer.c
purpose:test the time
creator:Bruse li
create time:2012-08-09
*/
#include<fcntl.h>
#include<stdio.h>
void main()
{
	int fd;
	int counter =0;
	int old_counter=0;
	//打开设备文件
	fd=open("/dev/second",O_RDONLY);
	if(fd!=-1)
	{
		while(1){
			read(fd,&counter,sizeof(unsigned int));//读目前经历的秒数
			if(counter!=old_counter){
				printf("seconds after open /dev/second :%d\n",counter);
				old_counter=counter;
			}
		}
	}else{
		printf("Device open failure\n");
	}
}
