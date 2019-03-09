CXX = g++

UNAME := $(shell uname)

BASEDIR=..
PATH+=:/home/scorbeau/Viveris/wxWidgetInstall/bin
INCS = -I../../../lib_jtag_core/src/
#INCLUDES = -I../../../../wxWidgets-3.1.2/include

CFLAGS  += -O3 `wx-config --cxxflags` -Wall $(INCS) # -Werror 
LDFLAGS += `wx-config --libs` -L../../../lib_jtag_core/build/linux -ljtag-core-static

EXEC=JTAGBoundaryScanner

ifeq ($(UNAME), Linux)
CFLAGS += -fPIC
endif

all: $(EXEC)

$(EXEC): JTAGBoundaryScanner.o MainFrame.o ProbeData.o ProbePage.o MainPage.o \
         I2cPage.o SpiPage.o MdioPage.o ProcessorPage.o ProcessorData.o \
         GpioData.o
	$(CXX) $^ $(LDFLAGS) -o $@

JTAGBoundaryScanner.o: $(BASEDIR)/JTAGBoundaryScanner.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MainFrame.o: $(BASEDIR)/gui/MainFrame.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

#MainPanel.o: $(BASEDIR)/gui/MainPanel.cpp
#	$(CXX) -o $@ -c $< $(CFLAGS)

ProbeData.o: $(BASEDIR)/model/ProbeData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

ProcessorData.o: $(BASEDIR)/model/ProcessorData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

GpioData.o: $(BASEDIR)/model/GpioData.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

ProbePage.o: $(BASEDIR)/gui/ProbePage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

I2cPage.o: $(BASEDIR)/gui/I2cPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

SpiPage.o: $(BASEDIR)/gui/SpiPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MdioPage.o: $(BASEDIR)/gui/MdioPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

ProcessorPage.o: $(BASEDIR)/gui/ProcessorPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

MainPage.o: $(BASEDIR)/gui/MainPage.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o $(EXEC)

mrproper: clean
	rm -rf $(EXEC)

.PHONY: clean mrproper

