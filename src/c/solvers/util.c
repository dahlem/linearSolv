/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <math.h>

#include <gsl/gsl_linalg.h>

#include "util.h"



int isPositiveDefinite(gsl_matrix *A)
{
    gsl_matrix *temp;

    temp = gsl_matrix_alloc(A->size1, A->size2);
    
    if (gsl_linalg_cholesky_decomp(temp) == GSL_EDOM) {
        gsl_matrix_free(temp);
        return MATRIX_NOT_POS_DEF;
    }

    gsl_matrix_free(temp);
    
    return 0;
}


void gatherErrors(gsl_vector *x_bar, gsl_vector *x, gsl_vector **x_error,
    double *max_error)
{
    double elem;
    size_t i;
    
    *x_error = gsl_vector_alloc(x_bar->size);
    gsl_vector_memcpy(*x_error, x);
    gsl_vector_sub(*x_error, x_bar);

    *max_error = fabs(gsl_vector_get(*x_error, 0));
    
    for (i = 1; i < (*x_error)->size; ++i) {
        elem = fabs(gsl_vector_get(*x_error, i));

        if (*max_error < elem) {
            *max_error = elem;
        }
    }
}
