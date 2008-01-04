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
 * Declaration of the methods for forwards/backwards substitution.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __SUBST_H__
#define __SUBST_H__


#include <stdbool.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>


#define NOT_UPPER_TRIANGULAR    11



bool isUpper(gsl_matrix *M);
int subst_backwards(gsl_matrix *M, gsl_vector **x_bar);
int subst_forwards(gsl_matrix *M, gsl_vector **x_bar);



#endif
