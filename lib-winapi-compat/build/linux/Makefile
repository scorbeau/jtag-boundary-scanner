CC = gcc
AR = ar

BASEDIR=$(shell pwd)/../..
INCDIR=$(BASEDIR)/include
SRCDIR=$(BASEDIR)/src

INCS=-I$(INCDIR)

CFLAGS=-O3 $(INCS) -Wall -Werror

LDFLAGS=-shared

STATIC_LIB=libwinapi-compat-static.a
DYNAMIC_LIB=libwinapi-compat.so

ifeq ($(UNAME), Linux)
CFLAGS += -fPIC
endif

OBJS=winapi_compat.o winapi_compat_error.o winapi_compat_module.o \
     winapi_compat_fs.o winapi_compat_core.o

all: $(STATIC_LIB) $(DYNAMIC_LIB)
	cp $(STATIC_LIB) $(BASEDIR)/libs
	cp $(DYNAMIC_LIB) $(BASEDIR)/libs

$(STATIC_LIB): $(OBJS)
	$(AR) rcs $@   $^

$(DYNAMIC_LIB): $(OBJS)
	$(CC) -o $@    $^ $(LDFLAGS)

winapi_compat.o: $(SRCDIR)/winapi_compat.c
	$(CC) -o $@ -c $< $(CFLAGS)

winapi_compat_error.o: $(SRCDIR)/winapi_compat_error.c
	$(CC) -o $@ -c $< $(CFLAGS)

winapi_compat_module.o: $(SRCDIR)/winapi_compat_module.c
	$(CC) -o $@ -c $< $(CFLAGS)

winapi_compat_fs.o: $(SRCDIR)/winapi_compat_fs.c
	$(CC) -o $@ -c $< $(CFLAGS)

winapi_compat_core.o: $(SRCDIR)/winapi_compat_core.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(STATIC_LIB) $(DYNAMIC_LIB)
	rm -rf $(BASEDIR)/libs/$(STATIC_LIB)
	rm -rf $(BASEDIR)/libs/$(DYNAMIC_LIB)

.PHONY: clean mrproper
