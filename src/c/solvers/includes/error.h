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
 * Declaration of the error codes for the linear algebra solvers.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __ERROR_H__
#define __ERROR_H__


/**
 * @defgroup Error codes
 * @{
 */

/**
 * Error code if the matrix is not rectangular
 */
#define MATRIX_NOT_RECTANGULAR          11

/**
 * Error code if the row of a matrix is out of bounds
 */
#define ROW_OUT_OF_BOUNDS               12

/**
 * Error code if the column of a matrix is out of bounds
 */
#define COLUMN_OUT_OF_BOUNDS            13

/**
 * Error code if the matrix-vector dimensions do not match
 */
#define MATRIX_VECTOR_UNEQUAL_ROW_DIM   14

/**
 * Error code if the matrix is not positive definite
 */
#define MATRIX_NOT_POS_DEF              15

/**
 * Error code if the matrix is not square
 */
#define MATRIX_NOT_SQUARE               16

/**
 * Error code if the matrix has linear dependent columns
 */
#define MATRIX_LINEAR_DEPENDENT_COLS    17

/** @}*/



#endif
