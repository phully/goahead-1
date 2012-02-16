##
## Makefile
##
## History:
##    2009/11/16 - [Qiao Wang]
##
## Copyright (C) 2004-2009, Ambarella, Inc.
##
## All rights reserved. No Part of this file may be reproduced, stored
## in a retrieval system, or transmitted, in any form, or by any means,
## electronic, mechanical, photocopying, recording, or otherwise,
## without the prior consent of Ambarella, Inc.
##

default: all

PWD			:= $(shell pwd)
MODULE_DIR		:= $(word 2, $(subst /unit_test/private/, ,$(PWD)))
PRIVATE_DIR		:= $(shell echo ./$(MODULE_DIR)|sed 's/\/[0-9a-zA-Z_]*/\/../g' )
AMBABUILD_TOPDIR	:= $(PWD)/$(PRIVATE_DIR)/../..
MODULE_NAME		:= "NTP Server"
LINK_FLAG	:= -L $(AMBABUILD_TOPDIR)/prebuild/lib -lpthread

LIBRARY= NTPServer
LIBDIR= uuid

export AMBABUILD_TOPDIR

include $(AMBABUILD_TOPDIR)/build/unit_test/common.mk

UNIT_TEST_LDFLAG	?= $(AMBARELLA_LDFLAGS)
UNIT_TEST_CFLAG	?= $(AMBARELLA_CFLAGS) -g -O0 -Wall

CC = $(AMBA_MAKEFILE_V)$(CROSS_COMPILE)gcc

srcdir = .

OBJS =	ntp.o

.PHONY: all clean

all : $(LIBRARY)

$(LIBRARY): $(OBJS)
	@echo "    compile NTP Server ..."
	@$(CC) $(UNIT_TEST_CFLAG) -o $(LIBRARY) $(OBJS) $(UNIT_TEST_LDFLAG)

clean:
	$(AMBA_MAKEFILE_V)echo "  [Clean $(MODULE_NAME)]:"
	$(AMBA_MAKEFILE_V)rm -f *.o $(LIBRARY)

# +++ Dependency line eater +++
# 
# Makefile dependencies follow.  This must be the last section in
# the Makefile.in file
#
NTP.o: NTP.c

.c.o:
	$(CC) $(UNIT_TEST_CFLAG) -c $< 




