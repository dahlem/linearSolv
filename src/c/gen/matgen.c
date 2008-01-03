/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdlib.h>
#include <string.h>

#include <gsl/gsl_blas.h>
#include <gsl/gsl_rng.h>

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


int randSPD(const gsl_rng *const rng, const double scale, gsl_matrix *mat)
{
    size_t i, j;
    double abs_value;
    
    
    if ((mat->size1 < 2) || (mat->size2 < 2)) {
        return MATRIX_TOO_SMALL;
    }
    if (mat->size1 != mat->size2) {
        return MATRIX_NOT_SYMMETRIC;
    }
    if (scale == 0) {
        return ZERO_SCALE;
    }

    for (i = 0; i < mat->size1; ++i) {
        for (j = i+1; j < mat->size2; ++j) {
            gsl_matrix_set(mat, i, j, scale * getRNG(rng));
            gsl_matrix_set(mat, j, i, gsl_matrix_get(mat, i, j));
        }
    }

    for (i = 0; i < mat->size1; ++i) {
        abs_value = 0.0;
        
        for (j = 0; j < mat->size2; ++j) {
            abs_value += abs(gsl_matrix_get(mat, i, j));
        }

        gsl_matrix_set(mat, i, i, abs_value + scale * gsl_rng_uniform(rng));
    }

    return 0;
}


int linsolv(const gsl_rng *const rng, const size_t dim, const double scale,
            gsl_matrix **mat, gsl_vector **b)
{
    int status;
    gsl_vector *x;


    *mat = gsl_matrix_calloc(dim, dim);

    if ((status = randSPD(rng, scale, *mat)) != 0) {
        return status;
    }

    x = gsl_vector_alloc(dim);
    gsl_vector_set_all(x, -1.0);
    
    *b = gsl_vector_calloc(dim);
    status = gsl_blas_dgemv(CblasNoTrans, 1.0, *mat, x, 0.0, *b);

    gsl_vector_free(x);
    
    return status;
}
