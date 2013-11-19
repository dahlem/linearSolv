/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

/**
 * Declaration of utility methods.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __UTIL_H__
#define __UTIL_H__


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "error.h"


/**
 * Check whether the matrix is positive definite.
 * 
 * @param gsl_matrix* the matrix to be checked.
 * @return 1, if true.
 */
int isPositiveDefinite(gsl_matrix *A);

/**
 * Gather the error statistics. The x_error vector is allocated within this function
 * and therefore must be de-allocated by the client application.
 *
 * @param gsl_vector* the x_bar vector
 * @param gsl_vector* the x vector
 * @param gsl_vector** the x_error vector
 * @param double* the maximum error
 */
void gatherErrors(gsl_vector *x_bar, gsl_vector *x, gsl_vector **x_error,
                  double *max_error);



#endif
