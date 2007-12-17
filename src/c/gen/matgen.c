/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <gsl/gsl_rng.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"
#include "matgen.h"


/**
 * Returns a uniform random number \f$ \in (-1,1) \f$
 *
 * @return a uniform random double number
 */
double getRNG(const gsl_rng *const rng)
{
    return 2.0 * gsl_rng_uniform(rng) - 1.0;
}


int randSPD(const gsl_rng *const rng, const double scale, matrix_t *mat)
{
    int i, j;
    double abs_value;
    
    
    if ((mat->r < 2) && (mat->c < 2) && (mat->c != mat->r)) {
        return MATRIX_NOT_SYMMETRIC;
    }
    if (scale == 0) {
        return ZERO_SCALE;
    }

    for (i = 0; i < mat->r; ++i) {
        for (j = i+1; j < mat->c; ++j) {
            mat->matrix[i][j] = scale * getRNG(rng);
            mat->matrix[j][i] = mat->matrix[i][j];
        }
    }

    for (i = 0; i < mat->r; ++i) {
        abs_value = 0.0;
        
        for (j = i+1; j < mat->c; ++j) {
            abs_value += abs(mat->matrix[i][j]);
        }

        mat->matrix[i][i] = abs_value + scale * getRNG(rng);
    }

    return 0;
}
