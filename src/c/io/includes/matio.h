/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __MATIO_H__
#define __MATIO_H__

#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>



#define COULD_NOT_READ_FILE     11
#define PREMATURE_END_OF_STREAM 12
#define UNKNOWN_TOKEN           13
#define ILLEGAL_FORMAT          14
#define CANNOT_SKIP             15


#define MAX_LINE_BUFFER  1025
#define MAX_TOKEN_BUFFER 128


#define ROW_SPEC "rows:"
#define COL_SPEC "columns:"


int read(const char * const filename, gsl_matrix **mat, gsl_vector **vec);
int write(const char * const filename, gsl_matrix *mat, gsl_vector *vec);


#endif
