/*
file name:test.c
purpose:test the ioctl 
creator:Bruse
create time:2012-08-07
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<linux/ioctl.h>
#define RANGE 1024
#define IOCTL_NAME  "create_ioctl"//定义设备名

#define TEST_MAGIC_NUM 'k'
#define CHARDEV_IOCPRINT  _IO(TEST_MAGIC_NUM,1)
#define CHAR_READ _IOW(TEST_MAGIC_NUM,1,int)
#define CHAR_WRITE _IOR(TEST_MAGIC_NUM,1,int)
int main(void)
{	
	int num;
	int fd =open("/dev/create_ioctl",O_RDWR);
	if(fd<0)
	{
		perror("open device");
		exit(fd);
	}
	ioctl(fd,CHAR_WRITE,&num);
	printf("begin ioctl\n");
	printf("%d   \n",num);
	close(fd);
	return 0;
}


