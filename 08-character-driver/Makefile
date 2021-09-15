# SPDX-License-Identifier: GPL-2.0
#

ifneq (${KERNELRELEASE},)

	obj-m += example-VIII-01.o
	obj-m += example-VIII-02.o
	obj-m += example-VIII-03.o
	obj-m += example-VIII-04.o
	obj-m += example-VIII-05.o
	obj-m += example-VIII-06.o
	obj-m += example-VIII-07.o
	obj-m += example-VIII-08.o

else

	KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build
	MODULE_DIR := $(shell pwd)

	USERSPACE  := example-ioctl
	USERSPACE  += ioctl-example-VIII-06

.PHONY: all

all: modules $(USERSPACE)

.PHONY: modules

modules:
	${MAKE} -C ${KERNEL_DIR} M=${MODULE_DIR}  modules

.PHONY: clean

clean:
	rm -f *.o *.ko *.mod.c .*.o .*.o.d .*.ko .*.mod.c .*.cmd *~ *.ko.unsigned *.mod
	rm -f Module.symvers Module.markers modules.order
	rm -rf .tmp_versions .cache.mk
	rm -f $(USERSPACE)

endif
