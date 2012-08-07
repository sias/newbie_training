
#file name:Makefile
#purpose:compile char_ioctl_driver.c
#creator:Bruse li
#create time:2012-08-07

obj-m +=char_ioctl.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD)
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
