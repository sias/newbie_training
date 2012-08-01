
#file name:char_driver5.c
#purpose:char device driver
#creator:Bruse
#creat time:2012-08-01

obj-m +=char_driver5.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
#KDIR = /lib/modules/$(KVER)/build
all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD)
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
