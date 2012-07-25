KVERDIR = /lib/modules/$(shell uname -r)/build
obj-m += luck.o
build:modules
modules:
	make -C $(KVERDIR) M=`pwd` modules
clean:
	make -C $(KVERDIR) M=`pwd` clean
