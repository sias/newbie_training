/*
file name:luck.c
purpose:simple luck word module
creator:bruse
creat time:2012-07-25

modify history:
Bruse Li,2012-07-26
*/
KVERDIR = /lib/modules/$(shell uname -r)/build
obj-m += luck.o
build:modules
modules:
	make -C $(KVERDIR) M=`pwd` modules
clean:
	make -C $(KVERDIR) M=`pwd` clean
