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



/**
 * @defgroup Error codes for the io library
 * @{
 */

/**
 * Error code if the file cannot be read (might not exist).
 */
#define COULD_NOT_READ_FILE     11

/**
 * Error code if the file ends prematurely.
 */
#define PREMATURE_END_OF_STREAM 12

/**
 * Error code if an unknown token was detected.
 */
#define UNKNOWN_TOKEN           13

/**
 * Error code if the file format does not match.
 */
#define ILLEGAL_FORMAT          14

/**
 * Error code if the specified number of lines cannot be skipped.
 */
#define CANNOT_SKIP             15

/** @}*/


/**
 * @defgroup Library settings
 * @{
 */

/**
 * Buffer to read in a line from the file
 */
#define MAX_LINE_BUFFER  1025

/**
 * Buffer for the maximum number of tokens
 */
#define MAX_TOKEN_BUFFER 128


/**
 * The row specification of the octave text file
 */
#define ROW_SPEC "rows:"

/**
 * The column specification of the octave text file
 */
#define COL_SPEC "columns:"

/** @}*/


/**
 * read in a matrix A, a vector x, and a vector b. Memory for the matrix and vectors
 * are allocated with the function, therefore the client application has to clean up
 * the memory.
 *
 * @param const char* const the filename
 * @param gsl_matrix** the matrix A
 * @param gsl_vector** the vector x
 * @param gsl_vector** the vector b
 * @return 0, if success. Otherwise error code.
 */
int read(const char * const filename, gsl_matrix **mat, gsl_vector **x, gsl_vector **b);

/**
 * Write a matrix A, a vector x, and a vector b into the specified file.
 *
 * @param const char* const the filename
 * @param gsl_matrix* the matrix A
 * @param gsl_vector* the vector x
 * @param gsl_vector* the vector b
 * @return 0, if success. Otherwise error code.
 */
int write(const char * const filename, gsl_matrix *mat, gsl_vector *x, gsl_vector *b);


#endif
