/*
file name:timer.c
purpose:char timer driver
creator:Bruse li
create time:2012-08-09
*/
#include<linux/miscdevice.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/types.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/sched.h>
#include<linux/errno.h>
#include<linux/slab.h>
#include<asm/io.h>
#include<asm/system.h>
#include<asm/uaccess.h>
#include<linux/delay.h> 
#define MISC_NAME  "second"//定义设备名
//设置设备结构体
struct chardev_dev
{
	struct cdev cdev;//cdev 结构体
	atomic_t counter;
	struct timer_list stimer;
};
static struct chardev_dev *chardev_devp;
//定时器处理函数
static void second_timer_handle(unsigned long arg)
{
	mod_timer(&chardev_devp->stimer,jiffies + HZ);
	atomic_inc(&chardev_devp->counter);
	printk(KERN_NOTICE "current jiffies is %ld\n",jiffies);
}
//文件打开函数
int chardev_open(struct inode *inode,struct file *filp)
{
	init_timer(&chardev_devp->stimer);
	chardev_devp->stimer.function =&second_timer_handle;
	chardev_devp->stimer.expires=jiffies+HZ;

        add_timer(&chardev_devp->stimer);
	atomic_set(&chardev_devp->counter,0);
	return 0;
}
//文件释放函数
int chardev_release(struct inode *inode,struct file *filp)
{
	del_timer(&chardev_devp->stimer);
        return 0;
}
//读函数
ssize_t chardev_read(struct file *filp,char *buf,size_t size,loff_t *offp)
{
	int counter;
	counter=atomic_read(&chardev_devp->counter);
	if(put_user(counter,(int*)buf))
		return -EFAULT;
	else
		return sizeof(unsigned int);
}
//文件操作结构体
static struct file_operations chardev_fops = {
	.owner = THIS_MODULE,
	.open = chardev_open,
	.release  = chardev_release,
	.read = chardev_read,
};

static struct miscdevice misc_dev =
{
	.minor = MISC_DYNAMIC_MINOR,//次设备号
	.name = MISC_NAME,//设备名
	.fops = &chardev_fops,
};
//设备驱动加载模块
static int chardev_init(void)
{      //杂项设备，主设备号为10
	int ret;
	chardev_devp=kmalloc(sizeof(struct chardev_dev),GFP_KERNEL);
	memset(chardev_devp,0,sizeof(struct chardev_dev));
	ret = misc_register(&misc_dev);
	if (ret)
	{
		printk("misc_register error\n");
		return ret;
	}
	return 0;
}
static void chardev_exit(void)
{
	kfree(chardev_devp);
	misc_deregister(&misc_dev);
}
module_init(chardev_init);
module_exit(chardev_exit);
MODULE_LICENSE("Dual BSD/GPL");
