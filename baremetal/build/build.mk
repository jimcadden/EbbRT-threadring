MYDIR := $(dir $(lastword $(MAKEFILE_LIST)))

EBBRT_TARGET := threadring
EBBRT_APP_OBJECTS := threadring.o IOStreamHandler.o
EBBRT_APP_VPATH := $(abspath $(MYDIR)../src)
EBBRT_CONFIG := $(abspath $(MYDIR)../src/ebbrtcfg.h)

include $(abspath $(EBBRT_SRCDIR)/apps/ebbrtbaremetal.mk)
