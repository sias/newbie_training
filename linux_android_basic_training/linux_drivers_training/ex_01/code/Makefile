
#file name:Makefile
#purpose:simple luck word module
#creator:Bruse
#creat time:2012-07-25

#modify history:
#Bruse Li,2012-07-26

KVERDIR = /lib/modules/$(shell uname -r)/build
CURCLE=$(shell pwd)
obj-m += luck.o
build:modules
modules:
	make -C $(KVERDIR) M=$(CURCLE) modules
clean:
	make -C $(KVERDIR) M=$(CURCLE) clean
