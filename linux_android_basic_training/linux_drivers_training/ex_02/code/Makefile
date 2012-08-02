
#file name:Makefile
#purpose:complit char_driver5.c
#creator:Bruse
#creat time:2012-08-01
#modify history:
#Bruse li,2012-08-02

obj-m +=char_driver5.o
PWD  = $(shell pwd)
KVER = $(shell uname -r)
all:
	$(MAKE) -C /lib/modules/$(KVER)/build M=$(PWD)
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions
