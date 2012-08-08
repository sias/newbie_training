/*
file name:mutex.c
purpose:device driver about concurrency
creator:Bruse li
create time:2012-08-08
*/
#include <linux/module.h>
#include<linux/miscdevice.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include<linux/slab.h>
#include <asm/system.h>
#include <asm/uaccess.h> 
#define MISC_NAME  "misc_kitty"//定义设备名 
#define MEMDEV_SIZE 1024  //分配的内存大小
 
struct mem_dev
{
	unsigned int size;
	char*data;
	struct semaphore sem; 
	struct cdev mem_cdev;
};
struct mem_dev *chardev_devp; /*设备结构体指针*/
/*文件打开函数*/ 
static int mem_open(struct inode *inode,struct file *filp)
{
	printk("mem_open.\n");
	return 0;
}
 
static int mem_release(struct inode *inode,struct file *filp)
{
	printk("mem_release.\n");
	return 0;
}
 
static ssize_t mem_read(struct file *filp,char __user *buf, size_t size, loff_t *ppos)
{
	int ret = 0;
	struct mem_dev *dev;	
	unsigned long p;
	unsigned long count;
	printk("mem_read.\n");
	count= size;
	p= *ppos;
	//检查偏移量和数据大小的有效性
	if(p> MEMDEV_SIZE)
		return 0;
	if(count> (MEMDEV_SIZE-p))
		count= MEMDEV_SIZE - p;
	if(down_interruptible(&chardev_devp->sem))//锁定互斥信号量
		return -ERESTARTSYS;
	//读取数据到用户空间
	if(copy_to_user(buf,chardev_devp->data+p, count)){
		ret= -EFAULT;
		printk("copyfrom user failed\n");
	}else{
		*ppos+= count;
		ret= count;
		printk("read%ld bytes from dev\n", count);
	}
	up(&dev->sem);//解锁互斥信号量
	return ret;
}
 
static ssize_t mem_write(struct file *filp,const char __user *buf, size_t size, loff_t *ppos)//注意：第二个参数和read方法不同
{
	int ret = 0;
	unsigned long p;
	unsigned long count;
	printk("mem_write.\n");
	count= size;
	p= *ppos;
	if(p> MEMDEV_SIZE)
		return 0;
	if(count> (MEMDEV_SIZE-p))
		count= MEMDEV_SIZE - p;
	if(down_interruptible(&chardev_devp->sem))//锁定互斥信号量
		return-ERESTARTSYS;
	if(copy_from_user(chardev_devp->data+p,buf, count)){
		ret= -EFAULT;
		printk("copyfrom user failed\n");
	}else{
		*ppos+= count;
		ret= count;
		printk("write%ld bytes to dev\n", count);
	}
	up(&chardev_devp->sem);//解锁互斥信号量
	return ret;
} 
/*文件操作结构体*/
static const struct file_operations chardev_fops = {
	.owner= THIS_MODULE,
	.open= mem_open,
	.write= mem_write,
	.read= mem_read,
	.release= mem_release,
};
static struct miscdevice misc_dev={
	.minor = MISC_DYNAMIC_MINOR,//次设备号
	.name = MISC_NAME,//设备名
	.fops = &chardev_fops,
};

 /*设备驱动模块加载函数*/
static int __init memdev_init(void)
{
	int ret=0;
	//杂项设备，主设备号为10
	chardev_devp=kmalloc(sizeof(struct mem_dev),GFP_KERNEL);
	memset(chardev_devp,0,sizeof(struct mem_dev));
	ret = misc_register(&misc_dev);
	if(ret)
	{
		printk("misc_register error\n");
		return ret;
         }
	return 0;       
} 
static void memdev_exit(void)
{
	kfree(chardev_devp);
	misc_deregister(&misc_dev);
}
 
module_init(memdev_init);
module_exit(memdev_exit); 
MODULE_AUTHOR("Bruse");
MODULE_LICENSE("GPL");
