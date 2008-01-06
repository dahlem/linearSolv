# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = linsolvmain

linsolvmain_SOURCES =                                                 \
	main.c                                                        \
	linsolv-cl.c

linsolvmain_CPPFLAGS =                                                \
	-I./includes                                                  \
	-I$(top_srcdir)/src/c/solvers/includes                        \
	-I$(top_srcdir)/src/c/io/includes                             \
	-I$(top_srcdir)/src/c/gen/includes


LDADD =                                                               \
	$(top_srcdir)/src/c/solvers/libsolvers.la                     \
	$(top_srcdir)/src/c/io/libmatio.la                            \
	$(top_srcdir)/src/c/gen/libmatgen.la                    


include_HEADERS = includes
MAINTAINERCLEANFILES = Makefile.in
