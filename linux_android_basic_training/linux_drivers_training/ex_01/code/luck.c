/*
file name:luck.c
purpose:A simple module
creator:Bruse
creat time:2012-07-27
*/
#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int luck_init(void)
{
	printk(KERN_INFO "luck come\n");
	return 0;
}
static void luck_exit(void)
{

	printk(KERN_INFO "luck exit\n");
}
module_init(luck_init);
module_exit(luck_exit);
MODULE_AUTHOR("BRUSH ");
MODULE_DESCRIPTION("A SIMPLE  LUCK WORD MODULE");
MODULE_ALIAS("A SIMPLE MODULES");
