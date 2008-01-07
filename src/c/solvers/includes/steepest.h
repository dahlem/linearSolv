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
 * Declaration of the methods for the Steepest descent algorithm.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __STEEPEST_H__
#define __STEEPEST_H__


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "error.h"


/**
 * This method solves the linear system with the Steepest Descent method.
 * The vectors x_bar and x_error are allocated within this
 * method and therefore need to be de-allocated by the client application.
 *
 * @param gsl_matrix* the matrix A
 * @param gsl_vector* the vector b
 * @param gsl_vector* the vector x
 * @param gsl_vector** the solution vector x_bar
 * @param gsl_vector** the error vector x_error
 * @param double* the maximum error within the solution vector
 * @see jacobi_precondition(gsl_matrix*, gsl_matrix**)
 * @return 0, if success. Otherwise the error code.
 */
int steepest(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
             gsl_vector **x_bar, gsl_vector **x_error, double *max_error);



#endif
