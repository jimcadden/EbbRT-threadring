MYDIR := $(dir $(lastword $(MAKEFILE_LIST)))

app_sources := \
	threadring.cc \
	Printer.cc 

target := threadring

include $(abspath $(EBBRT_SRCDIR)/apps/ebbrthosted.mk)
