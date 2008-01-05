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


int steepest(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
           gsl_vector **x_bar, gsl_vector **x_error, double *max_error);



#endif
