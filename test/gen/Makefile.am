# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Rules for the test code (use `make check` to execute)
include $(top_srcdir)/mk/gcov.am

TESTS = gen_test
check_PROGRAMS = $(TESTS)

gen_test_SOURCES =                                                   \
	gen_suite.c                                                  \
	gen_test.c


gen_test_CPPFLAGS =                                                  \
	-I./includes                                                 \
	-I$(top_srcdir)/src/c/gen/includes


LDADD =                                                              \
	-lcunit                                                      \
	-lm                                                          \
	$(top_srcdir)/src/c/gen/libmatgen.la


include_HEADERS = includes


MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = $(TESTS) *.log
