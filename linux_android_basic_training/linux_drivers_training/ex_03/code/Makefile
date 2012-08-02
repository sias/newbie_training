
#file name:Makefile
#purpose:compile misc_driver.c
#creator:Bruse li
#create time:2012-08-02

obj-m +=misc_driver.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD)
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
