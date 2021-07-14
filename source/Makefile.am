AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include\
  -I$(G4_MAIN)/include 

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib \
  -L$(OFFLINE_MAIN)/lib64

pkginclude_HEADERS = \
  EICG4B0ZDCHitTree.h \
  EICG4B0ZDCSubsystem.h

lib_LTLIBRARIES = \
  libEICG4B0ZDC.la

libEICG4B0ZDC_la_SOURCES = \
  EICG4B0ZDCSubsystem.cc\
  EICG4B0ZDCDetector.cc\
  EICG4B0ZDCHitTree.cc\
  EICG4B0ZDCSteppingAction.cc

libEICG4B0ZDC_la_LIBADD = \
  -lphool \
  -lSubsysReco\
  -lg4detectors\
  -lg4testbench 

BUILT_SOURCES = testexternals.cc

noinst_PROGRAMS = \
  testexternals

testexternals_SOURCES = testexternals.cc
testexternals_LDADD   = libEICG4B0ZDC.la

testexternals.cc:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@

clean-local:
	rm -f $(BUILT_SOURCES)
