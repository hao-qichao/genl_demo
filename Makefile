obj-m := demo_genetlink_kern.o
KERNEL_DIR := /home/hqc/linux-3.10.0-327.el7
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD) modules
clean:
	rm *.o *.ko *.mod.c
