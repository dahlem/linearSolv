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
 * Declaration of the methods for forwards/backwards substitution.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __SUBST_H__
#define __SUBST_H__


#include <stdbool.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>


/**
 * @defgroup Error code
 * @{
 */

/**
 * Error code if the matrix is not in upper triangular form
 */
#define NOT_UPPER_TRIANGULAR    11

/** @}*/



/**
 * Checks whether the matrix M is in upper triangular form.
 *
 * @param gsl_matrix* the matrix to be checked.
 * @return true, if it is in upper triangular form. False otherwise.
 */
bool isUpper(gsl_matrix *M);

/**
 * Solves the upper triangular matrix M using the backwards substitution.
 *
 * @param gsl_matrix* the matrix to be solved.
 * @param gsl_vecotr** the solution vector
 * @return 0, if success. Otherwise the error code.
 */
int subst_backwards(gsl_matrix *M, gsl_vector **x_bar);

/**
 * Solves the lower triangular matrix M using the forwards substitution.
 *
 * @param gsl_matrix* the matrix to be solved.
 * @param gsl_vecotr** the solution vector
 * @return 0, if success. Otherwise the error code.
 */
int subst_forwards(gsl_matrix *M, gsl_vector **x_bar);



#endif
