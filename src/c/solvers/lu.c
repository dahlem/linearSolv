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
    gsl_matrix *ML, *MU, *L, *U;
    gsl_vector *vec, *y_bar;
    size_t j;
    int status;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    if ((status = crout(A, &L, &U))) {
        return status;
    }

    /* prepare the (L|b) matrix */
    ML = gsl_matrix_alloc(L->size1, L->size2 + 1);
    vec = gsl_vector_alloc(L->size2);
    
    for (j = 0; j < L->size2; ++j) {
        gsl_matrix_get_col(vec, L, j);
        gsl_matrix_set_col(ML, j, vec);
    }
    
    gsl_matrix_set_col(ML, ML->size2 - 1, b);

    /* solve the (L|b) matrix using forwards substitution */
    if ((status = subst_forwards(ML, &y_bar))) {
        return status;
    }

    /* prepare the (U|b) matrix */
    MU = gsl_matrix_alloc(U->size1, U->size2 + 1);
    
    for (j = 0; j < U->size2; ++j) {
        gsl_matrix_get_col(vec, U, j);
        gsl_matrix_set_col(MU, j, vec);
    }
    gsl_vector_free(vec);
    
    gsl_matrix_set_col(MU, MU->size2 - 1, y_bar);

    /* solve the (U|b) matrix using backwards substitution */
    if ((status = subst_backwards(MU, x_bar))) {
        return status;
    }

    gsl_vector_free(y_bar);
    gsl_matrix_free(ML);
    gsl_matrix_free(MU);
    gsl_matrix_free(L);
    gsl_matrix_free(U);

    /* get the error statistics */
    gatherErrors(*x_bar, x, x_error, max_error);
    
    return 0;
}
