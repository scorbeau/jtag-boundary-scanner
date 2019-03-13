CC=cl.exe
CXX=cl.exe
LIBX=lib.exe
LINK=link.exe

BASEDIR=$(MAKEDIR)\..\..

SRCDIR=$(BASEDIR)\src

INCS=/I$(SRCDIR)

CFLAGS=/O2 $(INCS) /nologo /DWIN32=1
#/Wall
# /Werror
LDFLAGS = /nologo

STATIC_LIB=lib_jtag_core.lib
#DYNAMIC_LIB=lib_jtag_core.dll

PROBES_DRIVERS = lpt_jtag_drv.obj jlink_jtag_drv.obj ftdi_jtag_drv.obj
PROTOCOLS_DRIVERS = i2c_over_jtag.obj mdio_over_jtag.obj spi_over_jtag.obj memory_over_jtag.obj

all: $(STATIC_LIB)
#$(DYNAMIC_LIB)

#lib_jtag_core.dll: jtag_core.obj dbg_logs.obj bsdl_loader.obj bsdl_strings.obj drv_loader.obj drivers_list.obj $(PROTOCOLS_DRIVERS) $(PROBES_DRIVERS)
#	$(LINK) $(LDFLAGS) /dll /out:$(DYNAMIC_LIB) *.obj 

lib_jtag_core.lib: jtag_core.obj dbg_logs.obj bsdl_loader.obj bsdl_strings.obj drv_loader.obj drivers_list.obj $(PROTOCOLS_DRIVERS) $(PROBES_DRIVERS)
	$(LIBX) $(LDFLAGS) /out:$(STATIC_LIB) *.obj 

jtag_core.obj:
	$(CC) /c $(SRCDIR)/$*.c $(CFLAGS)

dbg_logs.obj:
	$(CC) /c $(SRCDIR)/$*.c $(CFLAGS)

bsdl_loader.obj:
	$(CC) /c $(SRCDIR)/bsdl_parser/$*.c $(CFLAGS)

bsdl_strings.obj:
	$(CC) /c $(SRCDIR)/bsdl_parser/$*.c $(CFLAGS)

i2c_over_jtag.obj:
	$(CC) /c $(SRCDIR)/bus_over_jtag/$*.c $(CFLAGS)

mdio_over_jtag.obj:
	$(CC) /c $(SRCDIR)/bus_over_jtag/$*.c $(CFLAGS)

spi_over_jtag.obj:
	$(CC) /c $(SRCDIR)/bus_over_jtag/$*.c $(CFLAGS)

memory_over_jtag.obj:
	$(CC) /c $(SRCDIR)/bus_over_jtag/$*.c $(CFLAGS)

drv_loader.obj:
	$(CC) /c $(SRCDIR)/drivers/$*.c $(CFLAGS)

drivers_list.obj:
	$(CC) /c $(SRCDIR)/drivers/$*.c $(CFLAGS)

lpt_jtag_drv.obj:
	$(CC) /c $(SRCDIR)/drivers/lpt_jtag/$*.c $(CFLAGS)

jlink_jtag_drv.obj:
	$(CC) /c $(SRCDIR)/drivers/jlink_jtag/$*.c $(CFLAGS)

ftdi_jtag_drv.obj:
	$(CC) /c $(SRCDIR)/drivers/ftdi_jtag/$*.c $(CFLAGS)
	
clean:
	rm -rf *.obj

mrproper: clean
	rm -rf $(STATIC_LIB) $(DYNAMIC_LIB)

.PHONY: clean mrproper

