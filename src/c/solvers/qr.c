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
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "qr.h"
#include "error.h"
#include "subst.h"
#include "util.h"



int qr_fact(gsl_matrix *A, gsl_matrix **Q, gsl_matrix **R)
{
    size_t i, k;
    gsl_vector *col;
    gsl_vector_view q_coli, q_colk;
    double dotprod;

    if (A->size1 != A->size2) {
        return MATRIX_NOT_SQUARE;
    }

    *Q = gsl_matrix_calloc(A->size1, A->size2);
    *R = gsl_matrix_calloc(A->size1, A->size2);
    col = gsl_vector_calloc(A->size2);

    gsl_matrix_memcpy(*Q, A);

    for (i = 0; i < (*Q)->size1; ++i) {
        q_coli = gsl_matrix_column(*Q, i);
        gsl_matrix_set(*R, i, i, gsl_blas_dnrm2(&q_coli.vector));

        if (gsl_matrix_get(*R, i, i) == 0) {
            return MATRIX_LINEAR_DEPENDENT_COLS;
        } else {
            gsl_vector_scale(&q_coli.vector, 1 / gsl_matrix_get(*R, i, i));
        }

        for (k = i + 1; k < (*Q)->size2; ++k) {
            q_colk = gsl_matrix_column(*Q, k);
            gsl_blas_ddot(&q_coli.vector, &q_colk.vector, &dotprod);
            gsl_matrix_set(*R, i, k, dotprod);
            gsl_vector_memcpy(col, &q_coli.vector);
            gsl_vector_scale(col, gsl_matrix_get(*R, i, k));
            gsl_vector_sub(&q_colk.vector, col);
        }
    }

    gsl_vector_free(col);

    return 0;
}


int qr(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
       gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_matrix *M, *Q, *R;
    gsl_vector *vec;
    size_t j;
    int status;


    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }

/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    if ((status = qr_fact(A, &Q, &R))) {
        return status;
    }

    M = gsl_matrix_alloc(R->size1, R->size2 + 1);
    vec = gsl_vector_alloc(R->size2);

    for (j = 0; j < R->size2; ++j) {
        gsl_matrix_get_col(vec, R, j);
        gsl_matrix_set_col(M, j, vec);
    }

    gsl_blas_dgemv(CblasTrans, 1.0, Q, b, 0.0, vec);

    gsl_matrix_set_col(M, M->size2 - 1, vec);
    gsl_vector_free(vec);

    if ((status = subst_backwards(M, x_bar))) {
        return status;
    }

    /* get the error statistics */
    gatherErrors(*x_bar, x, x_error, max_error);

    gsl_matrix_free(M);
    gsl_matrix_free(Q);
    gsl_matrix_free(R);

    return 0;
}


int eigen(gsl_matrix *A, gsl_vector **e, double prec)
{
    gsl_matrix *Ak, *Q, *R;
    gsl_vector_view diag_view;
    gsl_vector *diag;
    size_t i, l;
    double error, temp;

    if (A->size1 != A->size2) {
        return MATRIX_NOT_SQUARE;
    }

    *e = gsl_vector_alloc(A->size1);
    diag = gsl_vector_alloc(A->size1);

    /* we leave matrix A unchanged and operate on a copy */
    Ak = gsl_matrix_alloc(A->size1, A->size2);
    gsl_matrix_memcpy(Ak, A);
    diag_view = gsl_matrix_diagonal(Ak);

    do {
        gsl_vector_memcpy(diag, &diag_view.vector);
        qr_fact(Ak, &Q, &R);
        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, R, Q, 0.0, Ak);

        /* find max error within the differences of the diagonal of Ak */
        error = fabs(gsl_vector_get(diag, 0)
                     - gsl_vector_get(&diag_view.vector, 0));

        for (i = 1; i < diag->size; ++i) {
            temp = fabs(gsl_vector_get(diag, i)
                        - gsl_vector_get(&diag_view.vector, i));
            if (temp > error) {
                error = temp;
            }
        }
    } while (error > prec);

    /* read the eigenvalues in reverse order */
    l = Ak->size1 - 1;
    for (i = 0; i < Ak->size1; ++i) {
        gsl_vector_set(*e, i, gsl_matrix_get(Ak, l, l));
        l--;
    }

    gsl_matrix_free(Q);
    gsl_matrix_free(R);
    gsl_matrix_free(Ak);
    gsl_vector_free(diag);

    return 0;
}
