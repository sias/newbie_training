#file name:Makefile
#purpose:compile timer.c
#creator:Bruse li
#create time:2012-08-09

obj-m +=timer.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD)
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
