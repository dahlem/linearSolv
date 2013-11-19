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
 * Declaration of some command-line arguments and a <code>struct</code> for
 * the command-line option values.
 *
 * @author Dominik Dahlem 
 */
#ifndef __LINSOLV_CL_H__
#define __LINSOLV_CL_H__


#include <stdbool.h>

/**
 * @defgroup Application Definition of default application settings
 * @{
 */

/**
 * The default dimension of the square matrix to be generated.
 */
#define DEFAULT_N 0

/**
 * The default input file for the matrix and vectors.
 */
#define DEFAULT_FILE NULL

/**
 * The default linear solver (set to the Gaussian elimination method).
 */
#define DEFAULT_SOLVER 'g'

/**
 * The default eigenvalue solver (default: do not calculate the eigenvalues).
 */
#define DEFAULT_EIGEN false

/**
 * The default eigenvalue solver (default: do not calculate the eigenvalues).
 */
#define DEFAULT_OUTPUT false

/** @}*/


/**
 * A structure to capture the global arguments passed into application on the
 * command-line.
 */
struct globalArgs_t {
    int n; /* dimension for a randomly generated matrix */
    char *file; /* file to read input matrix/vectors from */
    char s; /* linear solver */
    bool e; /* eigenvalue solver */
    bool o; /* output flag */
} globalArgs;


/**
 * Display the help message for this application.
 */
void displayHelp();

/**
 * Initialise the global parameters.
 */
void init();

/**
 * Process the command-line arguments passed into the application.
 *
 * @param int number of arguments
 * @param char** pointer to the character array representing the command-line
 *               parameters
 */
void process_cl(int argc, char **argv);



#endif
