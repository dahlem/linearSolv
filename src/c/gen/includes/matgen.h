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
 * Declaration of matrix generation functions.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __MATGEN_H__
#define __MATGEN_H__

#include <gsl/gsl_rng.h>


#define MATRIX_NOT_SYMMETRIC    11
#define ZERO_SCALE              12


int linsolv(const double scale, vector_t *vec, matrix_t *mat);
int randSPD(const gsl_rng *const rng, const double scale, matrix_t *mat);



#endif
