# Makefile for a pci429-4 kernel module

CC=gcc

# Define __SMP__ directive for sources
ifdef CONFIG_SMP
EXTRA_CFLAGS += -D__SMP__
endif

obj-m   += pci429-4.o
pci429-4-objs :=

KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

default: all
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	install -d $(DESTDIR)/lib/modules/$(shell uname -r)/pci429-4
	install -m 644 pci429-4.ko $(DESTDIR)/lib/modules/$(shell uname -r)/pci429-4

distclean:
	-rm -f pci429-4.ko Module.symvers

clean :
	-rm -f *.mod.c *.o .*.cmd .tmp_versions/* Module.symvers *~
	-rmdir .tmp_versions
