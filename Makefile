# CONFIG_MODULE_SIG=n is supposed to supress "loading out-of-tree module taints
# kernel" lines in /var/log/dmesg, but does not.
CONFIG_MODULE_SIG=0
obj-m += test-logger-mod.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	#make -C /usr/src/linux-hwe-5.19-5.19.0/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	#make -C /usr/src/linux-hwe-5.19-5.19.0/ M=$(PWD) clean

tags:
	ctags -R /usr/src/linux-headers-`uname -r`/include

