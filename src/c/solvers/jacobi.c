/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <math.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "jacobi.h"
#include "error.h"
#include "util.h"



int jacobi(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
           gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    size_t l, i, j;
    double temp;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    *x_bar = gsl_vector_alloc(x->size);
    gsl_vector_memcpy(*x_bar, x);
    
    for (l = 0; l < A->size1; ++l) {
        for (i = 0; i < A->size1; ++i) {
            temp = 0.0;
            
            for (j = 0; j < A->size2; ++j) {
                if (i != j) {
                    temp += gsl_matrix_get(A, i, j) * gsl_vector_get(*x_bar, j);
                }
            }

            gsl_vector_set(*x_bar, i, (gsl_vector_get(b, i) - temp) /
                           gsl_matrix_get(A, i, i));
        }
    }

    /* get the error statistics */
    gatherErrors(*x_bar, x, x_error, max_error);
    
    return 0;
}
