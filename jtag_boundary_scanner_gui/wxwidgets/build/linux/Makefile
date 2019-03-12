CXX = g++
STRIP = strip

UNAME := $(shell uname)

BASEDIR=$(shell pwd)/../..

# Application src
SRCDIR=$(BASEDIR)/src
INCDIR=$(SRCDIR)/inc

# wxWidgets path
WXWIDGETS_SRC=$(BASEDIR)/wxWidgets-3.1.2
WXWIDGETS_BUILD=$(WXWIDGETS_SRC)/linux_build
WXWIDGETS_INSTALL=$(BASEDIR)/wxWidgets-Install

# lib jtag core path
JTAG_CORE_PATH=$(BASEDIR)/../../lib_jtag_core
JTAG_CORE_INC=$(JTAG_CORE_PATH)/src
JTAG_CORE_LIB=$(JTAG_CORE_PATH)/build/linux

# Add wxWidgets to PATH
PATH += :$(WXWIDGETS_INSTALL)/bin

INCS = -I$(JTAG_CORE_INC) -I$(INCDIR)

CFLAGS  += -O3 `wx-config --cxxflags` -Wall $(INCS) # -Werror 
LDFLAGS += `wx-config --libs` -L$(JTAG_CORE_LIB) -ljtag-core-static

EXEC=JTAGBoundaryScanner

ifeq ($(UNAME), Linux)
CFLAGS += -fPIC
endif

all: $(EXEC)

# Just to compile and install wxWidgets
wxwidgetlib:
	rm -Rf $(WXWIDGETS_INSTALL) $(WXWIDGETS_BUILD)
	mkdir --parents $(WXWIDGETS_INSTALL)
	mkdir --parents $(WXWIDGETS_BUILD)
	cd $(WXWIDGETS_BUILD)												&& \
		../configure --prefix=$(WXWIDGETS_INSTALL) --disable-shared	&& \
		make															&& \
		make install

$(EXEC): JTAGBoundaryScanner.o MainFrame.o ProbeData.o ProbePage.o MainPage.o \
         I2cPage.o SpiPage.o MdioPage.o CpuPage.o CpuData.o PinData.o
	$(CXX) $^ $(LDFLAGS) -o $@
	$(STRIP) $@

JTAGBoundaryScanner.o: $(SRCDIR)/src/JTAGBoundaryScanner.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MainFrame.o: $(SRCDIR)/src/gui/MainFrame.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

ProbeData.o: $(SRCDIR)/src/model/ProbeData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

CpuData.o: $(SRCDIR)/src/model/CpuData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

PinData.o: $(SRCDIR)/src/model/PinData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

ProbePage.o: $(SRCDIR)/src/gui/ProbePage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

I2cPage.o: $(SRCDIR)/src/gui/I2cPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

SpiPage.o: $(SRCDIR)/src/gui/SpiPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MdioPage.o: $(SRCDIR)/src/gui/MdioPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

CpuPage.o: $(SRCDIR)/src/gui/CpuPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MainPage.o: $(SRCDIR)/src/gui/MainPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o $(EXEC)

mrproper: clean
	rm -rf $(EXEC)

.PHONY: clean mrproper

