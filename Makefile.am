# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
ACLOCAL_AMFLAGS = -I m4 -I /usr/share/aclocal

include mk/doxygen.am


SUBDIRS = src

if HAVE_CUNIT
SUBDIRS += test
endif


MAINTAINERCLEANFILES = "configure Makefile.in semantic.cache"
MOSTLYCLEANFILES = ${DX_CLEANFILES}

dist_doc_DATA =                                             \
	doc

EXTRA_DIST = \
	$(srcdir)/coverage \
	$(srcdir)/report \
	$(srcdir)/m4/ac_gcov.m4 \
	$(srcdir)/m4/ac_gcov.m4 \
	$(srcdir)/mk/gcov.am \
	$(srcdir)/mk/gcov-recursive.am \
	$(srcdir)/mk/doxygen.am \
	$(srcdir)/src/octave \
	$(srcdir)/test.dat

clean-local:
	rm -rf doc/doxygen/html

dist-hook:
	rm -rf `find $(distdir)/doc -name .gitignore`


if GCOV

COVOUT=./coverage
LCOVOUT=$(COVOUT)/lcov-reports
GENHTMLOUT=$(LCOVOUT)/html

lcov-prepare:
	rm -rf $(COVOUT)
	mkdir -p $(GENHTMLOUT)
	lcov --zerocounters --directory . --quiet

lcov: clean lcov-prepare all
	cd test && $(MAKE) $(AM_MAKEFLAGS) lcov

else
lcov: ;

endif



.PHONY: lcov lcov-prepare doxygen-run doxygen-doc $(DX_PS_GOAL) $(DX_PDF_GOAL)
