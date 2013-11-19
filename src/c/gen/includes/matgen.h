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
 * Declaration of matrix generation functions.
 *
 * @author Dominik Dahlem 
 */
#ifndef __MATGEN_H__
#define __MATGEN_H__

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>


/**
 * @defgroup Error codes
 * @{
 */

/**
 * Error code if the matrix is not symmetric
 */
#define MATRIX_NOT_SYMMETRIC    11

/**
 * Error code if the scale is 0.
 */
#define ZERO_SCALE              12

/**
 * Error code if the matrix is too small.
 */
#define MATRIX_TOO_SMALL        13

/** @}*/


/**
 * Solve a randomly generated linear system. The matrix and the solution vector b
 * are allocated within this function. The client application needs to clean up the
 * memory explicitly.
 *
 * @param const gsl_rng *const the GSL random number generator
 * @param const size_t the dimension of the matrix to be generated.
 * @param const double the scale to be used as a multiplicator for each matrix element
 * @param gsl_matrix** the matrix to be generated
 * @param gsl_vector** the solution vector b
 * @return 0, if success. Otherwise the error code.
 */
int linsolv(const gsl_rng *const rng, const size_t dim, const double scale,
            gsl_matrix **mat, gsl_vector **b);

/**
 * @param const gsl_rng *const the GSL random number generator
 * @param const double the scale to be used as a multiplicator for each matrix element
 * @param gsl_matrix* the matrix to be filled with the random numbers
 * @return 0, if success. Otherwise the error code.
 */
int randSPD(const gsl_rng *const rng, const double scale, gsl_matrix *mat);



#endif
