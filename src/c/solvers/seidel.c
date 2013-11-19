/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "seidel.h"
#include "error.h"
#include "util.h"



int seidel(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
           gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_vector *x_old;
    size_t l, i, j;
    double temp1, temp2;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    *x_bar = gsl_vector_alloc(x->size);
    x_old = gsl_vector_alloc(x->size);
    gsl_vector_memcpy(*x_bar, x);
    gsl_vector_memcpy(x_old, x);
    
    for (l = 0; l < A->size1; ++l) {
        for (i = 0; i < A->size1; ++i) {
            temp1 = 0.0;
            temp2 = 0.0;
            
            for (j = 0; j < A->size2; ++j) {
                if (i > j) {
                    temp1 += gsl_matrix_get(A, i, j) * gsl_vector_get(*x_bar, j);
                } else if (i < j) {
                    temp2 += gsl_matrix_get(A, i, j) * gsl_vector_get(x_old, j);
                }
            }

            gsl_vector_set(*x_bar, i, (gsl_vector_get(b, i) - temp1 - temp2) /
                           gsl_matrix_get(A, i, i));
        }

        gsl_vector_memcpy(x_old, *x_bar);
    }

    /* get the error statistics */
    gatherErrors(*x_bar, x, x_error, max_error);

    gsl_vector_free(x_old);
    
    return 0;
}
