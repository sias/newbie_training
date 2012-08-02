/*
file name:char_driver5.c
purpose:char device driver
creator:Bruse
creat time:2012-08-01
*/
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
#include<linux/device.h>  /*device create,class create*/
#define RANGE 1024
#define DEVICE_NAME  "creat_inode"//定义设备名
#define DEVICE_MAJOR  52    //手动定义设备的主设备号
#define DEVICE_MINOR  0     //定义次设备号
static int chardev_major = DEVICE_MAJOR ;
static int chardev_minor =DEVICE_MINOR;

// 设备结构体
struct chardev_dev
{
       struct cdev cdev;
       unsigned char str[RANGE];
};
static struct chardev_dev *chardev_devp;
static struct chardev_dev dev;
static struct class *simple_class;
int chardev_open(struct inode *inode,struct file *filp)
{
       // MOD_INC_USE_COUNT;
	filp->private_data=chardev_devp;
        return 0;
}
int chardev_release(struct inode *inode,struct file *filp)
{
       // MOD_DEC_USE_COUNT;
        return 0;
}
ssize_t chardev_read(struct file *filp,char *buff,size_t size,loff_t *offp)
{
	unsigned long p =*offp;
	unsigned int count=size;
	int ret=0;
	struct chardev_dev *dev =filp->private_data;//houde she bei jie guo ti zhi zhen
	if( p >= RANGE)
		return 0;
	if(count>RANGE-p)
		count = RANGE - p;
	if(copy_to_user(buff,(void *)(dev->str+p),count)){
//			ret = -EFAULT;
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
//int chardev_ioctl(struct inode *inode,struct file *filp,unsigned int cmd,unsigned long arg)
//{

//}
static struct file_operations chardev_fops = {

              .owner = THIS_MODULE,
              .open = chardev_open,
              .release  = chardev_release,
//              .ioctl = chardev_ioctl,
              .read = chardev_read,
              .write = chardev_write,
};

//设备驱动加载模块
static int chardev_init(void)
{	printk(KERN_WARNING "init int int int int int \n");
       int result;
       dev_t devno = MKDEV(chardev_major,chardev_minor);  
       if(chardev_major)   
              result = register_chrdev_region(devno,1,DEVICE_NAME); 
       else
       {   
              result = alloc_chrdev_region(&devno ,chardev_minor ,1,DEVICE_NAME);
              chardev_major = MAJOR(devno);
       }

       if(result < 0)
       return result;
       chardev_devp=kmalloc(sizeof(struct chardev_dev),GFP_KERNEL);
       memset(chardev_devp,0,sizeof(struct chardev_dev));	

       int err;
       devno = MKDEV (chardev_major,chardev_minor);
       cdev_init(&dev.cdev,&chardev_fops);
       dev.cdev.owner = THIS_MODULE; 
       dev.cdev.ops = &chardev_fops;  //建立设备文件操作与系统调用之间的连接
       err = cdev_add(&dev.cdev,devno,1);  //向系统添加该设备

       if(err)
              printk("Error %d ",err);

	printk(KERN_WARNING ",,,,,,,,,,,,,,,,,,\n");	
	simple_class=class_create(THIS_MODULE,DEVICE_NAME);
	if(IS_ERR(simple_class)){
		printk("ERR:cannot creat a simple class");
	}
	device_create(simple_class,NULL,MKDEV(chardev_major,chardev_minor),NULL,DEVICE_NAME);
		printk("I am in\n");
		return 0;
  
}
static void chardev_exit(void)
{
       device_destroy(simple_class,MKDEV(chardev_major,chardev_minor));
       class_destroy(simple_class);
       cdev_del(&dev.cdev);
       kfree(chardev_devp); 
       unregister_chrdev_region(MKDEV(chardev_major,chardev_minor),1);  //释放设备号
}
module_init(chardev_init);
module_exit(chardev_exit);
MODULE_LICENSE("Dual BSD/GPL");
