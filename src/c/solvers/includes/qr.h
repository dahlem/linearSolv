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
 * Declaration of the methods for the QR decomposition algorithm.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __QR_H__
#define __QR_H__


#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "error.h"


/**
 * This method implements the QR factorisation method using the algorithm described
 * in "Orthogonal Bases and the QR Algorithm" by Peter J. Olver (link from wikipedia's
 * QR algorithm page).
 * The matrices Q and R are allocated within this function and require the client
 * application to clean up the memory explicitly.
 *
 * @param gsl_matrix* the matrix A
 * @param gsl_matrix** the matrix Q
 * @param gsl_matrix** the matrix R
 * @return 0, if success. Otherwise the error code.
 */
int qr_fact(gsl_matrix *A, gsl_matrix **Q, gsl_matrix **R);

/**
 * This method solves the linear system with the QR decomposition method.
 * The vectors x_bar and x_error are allocated within this method and
 * therefore need to be de-allocated by the client application.
 *
 * @param gsl_matrix* the matrix A
 * @param gsl_vector* the vector b
 * @param gsl_vector* the vector x
 * @param gsl_vector** the solution vector x_bar
 * @param gsl_vector** the error vector x_error
 * @param double* the maximum error within the solution vector
 * @see qr_fact(gsl_matrix*, gsl_matrix**)
 * @return 0, if success. Otherwise the error code.
 */
int qr(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
       gsl_vector **x_bar, gsl_vector **x_error, double *max_error);

/**
 * This method calculates the eigenvalues of a given matrix A using the direct QR
 * decomposition method. The algorithm used is the simple iterative one without any
 * preprocessing step, such as tridiagonalising the matrix A with the Householder's
 * alorithm.
 * The vector e is allocated within this function and requires the client
 * application to clean up the memory explicitly.
 *
 * @param gsl_matrix* the matrix A
 * @param gsl_vector** the vector to hold the eigenvalues
 * @param double the specified precision required to stop the iteration.=
 * @return 0, if success. Otherwise the error code.
 */
int eigen(gsl_matrix *A, gsl_vector **e, double prec);


#endif
