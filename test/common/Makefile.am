# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

TESTS = globals_test
check_PROGRAMS = $(TESTS)

globals_test_SOURCES =                                               \
	common_suite.c                                               \
	globals_test.c


globals_test_CPPFLAGS =                                              \
	-I./includes                                                 \
	-I$(top_srcdir)/src/c/common/includes


LDADD = -lcunit                                                      \
	$(top_srcdir)/src/c/common/libglobals.la


include_HEADERS = includes


MAINTAINERCLEANFILES = Makefile.in
CLEANFILES = $(TESTS) *.log
