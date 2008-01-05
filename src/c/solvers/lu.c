/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "error.h"
#include "lu.h"
#include "subst.h"
#include "util.h"



int crout(gsl_matrix *A, gsl_matrix **L, gsl_matrix **U)
{
    size_t i, j, k;
    double temp;
    
    
    if (A->size1 != A->size2) {
        return MATRIX_NOT_SQUARE;
    }

    *U = gsl_matrix_calloc(A->size1, A->size2);
    gsl_matrix_set_identity(*U);

    *L = gsl_matrix_calloc(A->size1, A->size2);

    for (i = 0; i < A->size1; ++i) {
        gsl_matrix_set(*L, i, 0, gsl_matrix_get(A, i, 0));
        gsl_matrix_set(*U, 0, i, gsl_matrix_get(A, 0, i) / gsl_matrix_get(A, 0, 0));
    }

    for (i = 0; i < A->size1; ++i) {
        for (j = 1; j <= i; ++j) {
            if (j <= i) {
                temp = 0.0;

                for (k = 0; k < j; ++k) {
                    temp += gsl_matrix_get(*L, i, k) * gsl_matrix_get(*U, k, j);
                }

                gsl_matrix_set(*L, i, j, gsl_matrix_get(A, i, j) - temp);
            }
        }

        for (j = 1; j < A->size2; ++j) {
            if ((i > 0) && (i <= j)) {
                temp = 0.0;

                for (k = 0; k < i; ++k) {
                    temp += gsl_matrix_get(*L, i, k) * gsl_matrix_get(*U, k, j);
                }

                gsl_matrix_set(*U, i, j, (gsl_matrix_get(A, i, j) - temp) /
                               gsl_matrix_get(*L, i, i));
            }
        }
    }

    return 0;
}



int lu(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
       gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_matrix *M;
    gsl_vector *vec;
    size_t i, j;
    int status;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
//    if ((status = isPositiveDefinite(A))) {
//        return status;
//    }

    M = gsl_matrix_alloc(A->size1, A->size2 + 1);
    vec = gsl_vector_alloc(A->size2);
    
    for (j = 0; j < A->size2; ++j) {
        gsl_matrix_get_col(vec, A, j);
        gsl_matrix_set_col(M, j, vec);
    }
    gsl_vector_free(vec);
    
    gsl_matrix_set_col(M, M->size2 - 1, b);

    if ((status = triangular(M))) {
        return status;
    }
    if ((status = subst_backwards(M, x_bar))) {
        return status;
    }

    *x_error = gsl_vector_alloc((*x_bar)->size);
    gsl_vector_memcpy(*x_error, x);
    gsl_vector_sub(*x_error, *x_bar);

    *max_error = fabs(gsl_vector_get(*x_error, 0));
    
    for (i = 1; i < (*x_error)->size; ++i) {
        double elem = fabs(gsl_vector_get(*x_error, i));

        if (*max_error < elem) {
            *max_error = elem;
        }
    }
    
    gsl_matrix_free(M);
    
    return 0;
}
