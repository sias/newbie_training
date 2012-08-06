/*
file name:misc_driver.c
purpose:misc device driver
creator:Bruse li
create time:2012-08-02
modify history:
Bruse li,2012-08-06
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
#define RANGE 1024
#define MISC_NAME  "misc_err"//定义设备名

//设置设备结构体
struct chardev_dev
{
	struct cdev cdev;
	unsigned char str[RANGE];
};
static struct chardev_dev *chardev_devp;
int chardev_open(struct inode *inode,struct file *filp)
{
	filp->private_data=chardev_devp;
	return 0;
}
int chardev_release(struct inode *inode,struct file *filp)
{
	return 0;
}
ssize_t chardev_read(struct file *filp,char *buff,size_t size,loff_t *offp)
{
	unsigned long p =*offp;
	unsigned int count=size;
	int ret=0;
	struct chardev_dev *dev =filp->private_data;//获得设备结构体指针
	if( p >= RANGE)
		return 0;
	if(count>RANGE-p)
		count = RANGE - p;
	if(copy_to_user(buff,(void *)(dev->str+p),count)){
		ret = -EFAULT;
		printk(KERN_ALERT "something done\n");
	}else {
		*offp +=count;
		ret =count;
		printk(KERN_INFO "read %u byte(s)from %lu\n",count,p);
	}
	return ret;		
}

ssize_t chardev_write(struct file *filp,const char *buff,size_t size,loff_t *offp)
{
	unsigned long p =*offp;
	unsigned int count=size;
	int ret=0;
	struct chardev_dev *dev=filp->private_data;
	if(p>RANGE)
		return 0;
	if(count>RANGE-p)
		count=RANGE-p;
	if(copy_from_user(dev->str+p,buff,count)){
		ret =-EFAULT;
	}else {
		*offp += count;
		ret =count;
		printk(KERN_INFO "write %u byte",count);
	}
	return ret;
}

static struct file_operations misc_fops = {
	.owner = THIS_MODULE,
	.open = chardev_open,
	.release  = chardev_release,
	.read = chardev_read,
	.write = chardev_write,
};

static struct miscdevice misc_dev =
{	
	.minor = MISC_DYNAMIC_MINOR,//次设备号
	.name = MISC_NAME,//设备名
	.fops = &misc_fops,
};

//设备驱动加载模块
static int chardev_init(void)
{      
	int ret=0;
	chardev_devp=kmalloc(sizeof(struct chardev_dev),GFP_KERNEL);
	memset(chardev_devp,0,sizeof(struct chardev_dev));
	ret = misc_register(&misc_dev);
	if (ret)
	{
		printk("misc_register error\n");
		return ret;
	}
 
	return ret;
}
static void chardev_exit(void)
{	 
	kfree(chardev_devp);
	misc_deregister(&misc_dev);
}
module_init(chardev_init);
module_exit(chardev_exit);
MODULE_LICENSE("Dual BSD/GPL");
