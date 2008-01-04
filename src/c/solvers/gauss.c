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

#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>

#include "gauss.h"
#include "subst.h"


int largestPivot(gsl_matrix *M, size_t r, size_t c)
{
    size_t i, k;
    double maxElem;

    if (r >= M->size1) {
        return ROW_OUT_OF_BOUNDS;
    }
    if (c >= M->size2) {
        return COLUMN_OUT_OF_BOUNDS;
    }

    k = r;

    if (r == (M->size1 - 1)) {
        return k;
    }

    maxElem = gsl_matrix_get(M, r, c);

    for (i = r; i < M->size1; ++i) {
        double elem = gsl_matrix_get(M, i, c);

        if (elem > maxElem) {
            maxElem = elem;
            k = i;
        }
    }

    return k;
}


int pivotRow(gsl_matrix *M, size_t r, size_t c)
{
    size_t k;

    if (r >= M->size1) {
        return ROW_OUT_OF_BOUNDS;
    }
    if (c >= M->size2) {
        return COLUMN_OUT_OF_BOUNDS;
    }

    if (gsl_matrix_get(M, r, c) == 0) {
        return 0;
    }

    k = largestPivot(M, r, c);

    if (k == r) {
        return 0;
    }

    gsl_matrix_swap_rows(M, r, k);

    return 0;
}


int triangular(gsl_matrix *M)
{
    size_t i, j, k;
    gsl_vector_view vec_view1, vec_view2;
    

    if (M->size1 != (M->size2 - 1)) {
        return MATRIX_NOT_RECTANGULAR;
    }

    for (j = 0; j < (M->size2 - 2); ++j) {
        pivotRow(M, j, j);

        for (i = (j + 1); i < M->size1; ++i) {
            vec_view1 = gsl_matrix_row(M, i);
            vec_view2 = gsl_matrix_row(M, j);
            
            gsl_blas_daxpy(-gsl_matrix_get(M, i, j)/gsl_matrix_get(M, j, j),
                           &vec_view2.vector, &vec_view1.vector);
            for (k = 0; k < (&vec_view1.vector)->size; ++k) {
                gsl_vector_set(&vec_view1.vector, k,
                               fabs(gsl_vector_get(&vec_view1.vector, k)));
            }
        }
    }

    return 0;
}


int gauss(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
          gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_matrix *temp, *M;
    gsl_vector *vec;
    size_t i, j;
    int status;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
    temp = gsl_matrix_alloc(A->size1, A->size2);
    
//    if (gsl_linalg_cholesky_decomp(temp) == GSL_EDOM) {
//        gsl_matrix_free(temp);
//        return MATRIX_NOT_POS_DEF;
//    }

    gsl_matrix_free(temp);

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
