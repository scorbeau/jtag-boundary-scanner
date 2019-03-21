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

EXEC=sleep
EXEC_DYN=sleep-dyn

ifeq ($(UNAME), Linux)
CFLAGS += -fPIC
endif

all: $(EXEC) $(EXEC_DYN)

dynamic: $(EXEC_DYN)

$(EXEC): main.o
	$(CC) $^ $(LDFLAGS) -o $@
	$(STRIP) $@

$(EXEC_DYN): main.o
	$(CC) $^ $(LDFLAGS_DYN) -o $@
	$(STRIP) $@

main.o: $(SRCDIR)/main.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC) $(EXEC_DYN)

.PHONY: clean mrproper

