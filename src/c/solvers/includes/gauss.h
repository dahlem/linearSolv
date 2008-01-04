/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

/**
 * Declaration of the methods for gaussian elimination.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GAUSS_H__
#define __GAUSS_H__


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>


#define MATRIX_NOT_RECTANGULAR          11
#define ROW_OUT_OF_BOUNDS               12
#define COLUMN_OUT_OF_BOUNDS            13
#define MATRIX_VECTOR_UNEQUAL_ROW_DIM   14
#define MATRIX_NOT_POS_DEF              15


int triangular(gsl_matrix *M);
int largestPivot(gsl_matrix *M, size_t r, size_t c);
int pivotRow(gsl_matrix *M, size_t r, size_t c);

int gauss(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
          gsl_vector **x_bar, gsl_vector **x_error, double *max_error);



#endif
