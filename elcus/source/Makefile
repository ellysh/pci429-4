# Makefile for a Daq2213 kernel module
 
CC=gcc

ifdef CONFIG_SMP
EXTRA_CFLAGS += -D__SMP__
endif

ifneq ($(KERNELRELEASE),)
obj-m   += pci429-4.o
pci429-4-objs := 

else
KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

default: all
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
#	mkdir -p ../../drivers/$(shell uname -r)
#	mv daq2213.ko ../../drivers/$(shell uname -r)
#	strip --strip-debug --strip-unneeded ../../drivers/$(shell uname -r)/daq2213.ko
install:
	install -d $(DESTDIR)/lib/modules/$(shell uname -r)/pci429-4
	install -m 644 pci429-4.ko $(DESTDIR)/lib/modules/$(shell uname -r)/pci429-4
distclean:
	-rm -f pci429-4.ko Module.symvers
endif

clean :
	-rm -f *.mod.c *.o .*.cmd .tmp_versions/* Module.symvers *~
	-rmdir .tmp_versions
