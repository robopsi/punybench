#
############################################################################
# (C) Copyright 2008 Novell, Inc. All Rights Reserved.
#
#  GPLv2: This program is free software; you can redistribute it
#  and/or modify it under the terms of version 2 of the GNU General
#  Public License as published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
############################################################################

makedir := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
include $(makedir)/gnu.mk

ifeq ($(BOARD),)
  TARGET = $(shell uname -m)
else
  TARGET = $(BOARD)
endif

os      := $(shell uname)
optdir  := /opt/punybench
target  := $(TARGET)
objdir  :=.$(target)
sources := $(wildcard *.c)
headers := $(wildcard *.h)
objects := $(addprefix $(objdir)/, $(sources:.c=))
opuses  := $(sources:.c=)
bin      = $(DESTDIR)$(optdir)/bin

-include $(makedir)/$(target).mk

INC    += -I. -I../include -I../../include

CFLAGS += -rdynamic -fPIC
CFLAGS += -g -O -Wall -Wstrict-prototypes -Werror \
	-D_F=\"$(basename $(notdir $(<)))\" \
	-D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 \
	-D_GNU_SOURCE \
	$(.INCLUDES) $(INC) \

LIBS   += ../libpuny.b/$(objdir)/libpuny

ifeq ($(os),Linux)
	LIBS   += -lrt
endif

all: $(objects)

$(objdir)/% : %.c $(headers)
	@ mkdir -p $(objdir)
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

install:
	@ mkdir -p $(bin)
	cd $(objdir); cp $(opuses) $(bin)

.PHONEY : clean
clean:
	@ rm -fr $(objdir)
	@rm -f *.core
	@rm -f *.out
	@ cd $(bin) ; rm -f $(opuses)

cleanbin:
	@ cd $(bin) ; rm -f $(opuses)

test:
	@echo "objdir ="$(objdir)
	@echo "objects="$(objects)
	@echo "opuses ="$(opuses)
