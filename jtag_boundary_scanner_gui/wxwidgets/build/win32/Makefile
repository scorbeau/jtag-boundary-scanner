CC=cl.exe
CXX=cl.exe
LIBX=lib.exe
LINK=link.exe

BASEDIR=$(MAKEDIR)\..\..

# Application src
SRCDIR=$(BASEDIR)\src
INCDIR=$(SRCDIR)\inc

# wxWidgets path
WXWIDGETS_SRC=$(BASEDIR)\wxWidgets-3.1.2
WXWIDGETS_BUILD=$(WXWIDGETS_SRC)\build\msw
WXWIDGETS_INSTALL=$(WXWIDGETS_SRC)\lib\vc_lib
WXWIDGETS_INCS=/I$(WXWIDGETS_SRC)\include /I$(WXWIDGETS_INSTALL)\mswu
WXWIDGETS_CFLAGS=$(WXWIDGETS_INCS) /D__WXMSW__ /DNDEBUG /D_UNICODE /D_WINDOWS /DNOPCH
WXWIDGETS_LDFLAGS=/libpath:$(WXWIDGETS_INSTALL)
WXWIDGETS_LDFLAGS_EXTRA=wxmsw31u_core.lib  wxbase31u.lib wxtiff.lib wxjpeg.lib \
			wxpng.lib wxzlib.lib wxregexu.lib wxexpat.lib

# lib jtag core path
JTAG_CORE_PATH=$(BASEDIR)/../../lib_jtag_core
JTAG_CORE_INC=$(JTAG_CORE_PATH)/src
JTAG_CORE_LIB=$(JTAG_CORE_PATH)/build/win32
JTAG_CORE_CFLAGS=/I$(JTAG_CORE_INC)
JTAG_CORE_LDFLAGS=/libpath:$(JTAG_CORE_LIB) lib_jtag_core.lib

INCS=/I$(INCDIR)

CFLAGS=/nologo /TP /EHsc /GR /O2 $(INCS) /MD /DWIN32 $(WXWIDGETS_CFLAGS) \
	$(JTAG_CORE_CFLAGS) /D_CRT_SECURE_NO_DEPRECATE=1 \
	/D_CRT_NON_CONFORMING_SWPRINTFS=1 /D_SCL_SECURE_NO_WARNINGS=1 \
	/D__NO_VC_CRTDBG__
LDFLAGS=/nologo $(JTAG_CORE_LDFLAGS) $(WXWIDGETS_LDFLAGS) /opt:ref /opt:icf \
	/SUBSYSTEM:WINDOWS kernel32.lib user32.lib gdi32.lib comdlg32.lib \
	winspool.lib winmm.lib shell32.lib shlwapi.lib comctl32.lib ole32.lib \
	oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib version.lib wsock32.lib \
	wininet.lib

EXEC=JTAGBoundaryScanner.exe

all: $(EXEC)

# Just to compile and install wxWidgets
wxwidgetlib:
	cd $(WXWIDGETS_BUILD) && $(MAKE) /f makefile.vc BUILD=release

$(EXEC): JTAGBoundaryScanner.obj MainFrame.obj ProbeData.obj ProbePage.obj \
	MainPage.obj I2cPage.obj SpiPage.obj MdioPage.obj CpuPage.obj \
	CpuData.obj PinData.obj
	$(LINK) /out:$@ $(LDFLAGS)  *.obj

JTAGBoundaryScanner.obj:
	$(CXX) /c $(SRCDIR)/src/$*.cpp $(CFLAGS)

MainFrame.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

ProbeData.obj:
	$(CXX) /c $(SRCDIR)/src/model/$*.cpp $(CFLAGS)

CpuData.obj:
	$(CXX) /c $(SRCDIR)/src/model/$*.cpp $(CFLAGS)

PinData.obj:
	$(CXX) /c $(SRCDIR)/src/model/$*.cpp $(CFLAGS)

ProbePage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

I2cPage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

SpiPage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

MdioPage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

CpuPage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

MainPage.obj:
	$(CXX) /c $(SRCDIR)/src/gui/$*.cpp $(CFLAGS)

clean:
	rm -rf *.obj $(EXEC)

mrproper: clean
	rm -rf $(EXEC)

.PHONY: clean mrproper


