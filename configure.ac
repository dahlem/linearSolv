# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([563 - Assignment 1],
        [0.1],
        [Dominik Dahlem Dominik.Dahlem@cs.tcd.ie], 
        [563_linearsolv])


AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])

# extra autoconf macros
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

CFLAGS="-W -Wall -pedantic ${CFLAGS}"

LF_CONFIGURE_CC
LF_HOST_TYPE
LF_SET_WARNINGS

AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memset])

# GSL library checks
AC_CHECK_LIB([m],[cos])
AC_CHECK_LIB([gslcblas],[cblas_dgemm])
AC_CHECK_LIB([gsl],[gsl_blas_dgemm])


# enable cunit?
AC_ARG_ENABLE(test, AS_HELP_STRING(
		     [--enable-test], 
		     [enable test @<:@default=no@:>@]), 
		     [TESTING=$enableval], [TESTING=no])

# Check for cunit
if test x$TESTING = xyes; then
   AC_CHECK_LIB(cunit, CU_initialize_registry, HAVE_CUNIT="yes")
   
   if test x$HAVE_CUNIT != xyes; then
	AC_MSG_WARN([CUnit not found. Tests cannot be run.])
   fi
fi
AM_CONDITIONAL(HAVE_CUNIT, test "x$HAVE_CUNIT" = xyes)


# optional libraries
AC_GCOV


DX_DOXYGEN_FEATURE([ON])
DX_HTML_FEATURE([ON])
DX_CHM_FEATURE([OFF])
DX_CHI_FEATURE([OFF])
DX_MAN_FEATURE([OFF])
DX_RTF_FEATURE([OFF])
DX_XML_FEATURE([OFF])
DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([MPI-Heat], [Doxyfile], [doc/doxygen])


AC_CONFIG_FILES([
   Makefile
   src/Makefile
   src/c/Makefile
   src/c/gen/Makefile
   src/c/io/Makefile
   test/Makefile
   test/gen/Makefile
   test/io/Makefile
])


AC_OUTPUT

for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
  test -f $top_builddir/configure && break
done

AC_MSG_RESULT([

des $VERSION: Automatic configuration OK.

Type 'make' to compile this project.

])
