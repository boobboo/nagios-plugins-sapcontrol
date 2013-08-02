AM_CFLAGS = -I../$(np_srcdir)/plugins -I../$(np_srcdir)/lib -I../$(np_srcdir)/gl -I../$(np_srcdir)/intl

SOAPCPP2FILES = SAPControlClient.c SAPControlC.c SAPControlClientLib.c SAPControlH.h SAPControl.nsmap SAPControlStub.h

libexec_PROGRAMS = check_sapcontrol

BASEOBJS = ../$(np_srcdir)/plugins/utils.o ../$(np_srcdir)/lib/libnagiosplug.a ../$(np_srcdir)/gl/libgnu.a
SAPCONTROLOBJS = SAPControlC.o SAPControlClient.o $(BASEOBJS)
SAPCONTROLLIBS = $(SAPCONTROLOBJS) $(GSOAP_LIBS)

check_sapcontrol_LDADD = $(SAPCONTROLLIBS)
check_sapcontrol_CFLAGS = $(AM_CFLAGS) $(GSOAP_CFLAGS)

check_sapcontrol_DEPENDENCIES = check_sapcontrol.c $(SAPCONTROLOBJS) $(DEPLIBS)

BUILT_SOURCES = SAPControl.h SAPControlClient.c SAPControlC.c
CLEANFILES = SAPControl.h $(SOAPCPP2FILES)

SAPControlC.o: SAPControlC.c
SAPControlClient.o: SAPControlClient.c

SAPControlClient.c: SAPControl.h
	soapcpp2 -Ccwxp SAPControl SAPControl.h

SAPControl.h: Makefile 
	wsdl2h -o $@ -c SAPControl.wsdl
