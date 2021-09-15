##############################################################################
## Exemple de la formation "Temps-reel Linux et Xenomai"
##
## Christophe Blaess 2010-2018
## http://christophe.blaess.fr
## Licence GPLv2
##############################################################################

APPLICATIONS:=      \
  exemple-III-01    \
  exemple-III-02    \
  exemple-III-03    \
  exemple-III-04    \
  exemple-III-07    \
  exemple-III-08    \
  exemple-III-09    \
  exemple-III-10    \
  exemple-III-11    \
  exemple-III-12    \
  exemple-III-13    \


ifneq (${KERNELRELEASE},)

  obj-m += exemple-III-05.o
  obj-m += exemple-III-06.o


else

CFLAGS=-Wall -g -pthread
LDFLAGS=-pthread
LOADLIBES=-lrt
CC = ${CROSS_COMPILE}gcc
AS = ${CROSS_COMPILE}as
LD = ${CROSS_COMPILE}gcc

	CROSS_COMPILE ?=
	ARCH          ?=
	KERNEL_DIR    ?= /lib/modules/$(shell uname -r)/build
	MODULE_DIR    := $(shell pwd)

.PHONY: all
all: ${APPLICATIONS}

.PHONY: modules
modules:
	${MAKE} arch=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C ${KERNEL_DIR} SUBDIRS=${MODULE_DIR}  modules

.PHONY: clean
clean:
	rm -f ${APPLICATIONS} *.o *~
	rm -f *.o *.ko *.mod.c modules.order Module.symvers
	rm -rf .tmp_versions .*.cmd

endif
