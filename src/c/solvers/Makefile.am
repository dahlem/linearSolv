# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

noinst_LTLIBRARIES = libsolvers.la

libsolvers_la_SOURCES =                                               \
	subst.c                                                       \
	util.c                                                        \
	gauss.c                                                       \
	lu.c                                                          \
	chol.c                                                        \
	jacobi.c                                                      \
	seidel.c                                                      \
	steepest.c                                                    \
	conjugate.c                                                   \
	precondition.c                                                \
	qr.c

libsolvers_la_CPPFLAGS = -I./includes

LDADD =                                                               \
	-lgsl                                                         \
	-lgslcblas                                                    \
	-lm


include_HEADERS = includes
MAINTAINERCLEANFILES = Makefile.in
