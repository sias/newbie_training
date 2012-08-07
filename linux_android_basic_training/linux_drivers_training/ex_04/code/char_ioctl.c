/*
file name:char_ioctl.c
purpose:char device driver
creator:Bruse
create time:2012-08-07
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
#include<linux/device.h>  /*device_create,class_create*/
#include<linux/slab.h>
#include<linux/poll.h>
#define RANGE 1024
#define DEVICE_NAME  "create_ioctl"//定义设备名
#define DEVICE_MAJOR  57    //手动定义设备的主设备号
#define DEVICE_MINOR  0     //定义次设备号
#define CHARDEV_IOC_MAGIC 'k'
#define CHARDEV_IOCPRINT _IO(CHARDEV_IOC_MAGIC,1)
#define CHAR_WRITE  _IOR(CHARDEV_IOC_MAGIC,1,int)
#define CHAR_READ _IOW(CHARDEV_IOC_MAGIC,3,int)
#define CHARDEV_IOC_MAXNR 3
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
	struct chardev_dev *dev =filp->private_data;/*获得设备结构提指针*/
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

long chardev_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	int ret=0;
	int ioarg=0;
	switch(cmd)
	{	
		case CHARDEV_IOCPRINT:
			printk(" cmd chardev_iocprint done\n");
			break;
		case CHAR_WRITE:
			printk("cmd put_user\n");
			ioarg=110;
			ret=__put_user(ioarg,(int *)arg);
			break;
		case CHAR_READ:
			ret=__get_user(ioarg,(int *)arg);
			break;
		default:
			return -EINVAL;
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
/*初始化file_operatioms结构*/
static struct file_operations chardev_fops = {
	.owner = THIS_MODULE,
	.open = chardev_open,
	.release  = chardev_release,
	.read = chardev_read,
	.unlocked_ioctl=chardev_ioctl,
	.write = chardev_write,
};

/*设备驱动加载模块*/
static int chardev_init(void)
{      
	int result=0;
	int err =0;	
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

	devno = MKDEV (chardev_major,chardev_minor);
	cdev_init(&dev.cdev,&chardev_fops);
	dev.cdev.owner = THIS_MODULE; 
	dev.cdev.ops = &chardev_fops;  //建立设备文件操作与系统调用之间的连接
	err = cdev_add(&dev.cdev,devno,1);  //向系统添加该设备
     
	if(err)
		printk("Error %d ",err);
	
	simple_class=class_create(THIS_MODULE,DEVICE_NAME);
	if(IS_ERR(simple_class)){
		printk("ERR:cannot creat a simple class");
	}
	device_create(simple_class,NULL,MKDEV(chardev_major,chardev_minor),NULL,DEVICE_NAME);
		printk("Have Created an inode under dev\n");
		return 0;
}
//设备驱动卸载模块
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
MODULE_AUTHOR("Bruse");
MODULE_LICENSE("Dual BSD/GPL");
