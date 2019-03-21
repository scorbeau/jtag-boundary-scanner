CC = gcc
CXX = g++
STRIP = strip

UNAME := $(shell uname)

BASEDIR=$(shell pwd)
SRCDIR=$(BASEDIR)

# lib path
WINAPI_COMPAT_INC=$(BASEDIR)/../../include
WINAPI_COMPAT_LIB=$(BASEDIR)/../../build/linux
WINAPI_LDFLAGS_STATIC=-L$(WINAPI_COMPAT_LIB) -lwinapi-compat-static -ldl
WINAPI_LDFLAGS_DYNAMIC=-L$(WINAPI_COMPAT_LIB) -lwinapi-compat -ldl

INCS = -I$(WINAPI_COMPAT_INC)

CFLAGS  += -O3 $(INCS) -Wall -Werror
LDFLAGS += $(WINAPI_LDFLAGS_STATIC)
LDFLAGS_DYN = $(LDFLAGS) $(WINAPI_LDFLAGS_DYNAMIC)

EXEC=module-load
EXEC_DYN=module-load-dyn

LOCAL_LIB=libmodule-load.so

ifeq ($(UNAME), Linux)
CFLAGS += -fPIC
endif

all: $(EXEC) $(EXEC_DYN) $(LOCAL_LIB)

static: $(EXEC) $(LOCAL_LIB)

dynamic: $(EXEC_DYN) $(LOCAL_LIB)

$(EXEC): main.o
	$(CC) $^ $(LDFLAGS) -o $@
	$(STRIP) $@

$(EXEC_DYN): main.o
	$(CC) $^ $(LDFLAGS_DYN) -o $@
	$(STRIP) $@

$(LOCAL_LIB): module_load.o
	$(CC) -o $@ $^ -shared

main.o: $(SRCDIR)/main.c
	$(CC) -o $@ -c $< $(CFLAGS)

module_load.o: $(SRCDIR)/module_load.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) $(EXEC_DYN)

.PHONY: clean mrproper

