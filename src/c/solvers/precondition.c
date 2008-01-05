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

#include "precondition.h"
#include "error.h"
#include "util.h"


int jacobi_precondition(gsl_matrix *A, gsl_matrix **M1)
{
    size_t i;
    
    if (A->size1 != A->size2) {
        return MATRIX_NOT_SQUARE;
    }

    *M1 = gsl_matrix_calloc(A->size1, A->size2);

    for (i = 0; i < A->size1; ++i) {
        gsl_matrix_set(*M1, i, i, sqrt(gsl_matrix_get(A, i, i)));
    }
}


int precondition(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
                 gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_vector *r, *temp, *z, *d;
    gsl_matrix *M1;
    size_t k, n;
    double dotprod, alpha, beta, rho;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    *x_bar = gsl_vector_calloc(x->size);
    r = gsl_vector_calloc(x->size);
    z = gsl_vector_calloc(x->size);
    d = gsl_vector_calloc(x->size);

    k = 1;
    n = A->size1;
    gsl_vector_memcpy(*x_bar, x);
    gsl_vector_memcpy(r, b);
    gsl_blas_dgemv(CblasNoTrans, -1.0, A, *x_bar, 1.0, r);

    jacobi_precondition(A, &M1);
    gsl_vector_memcpy(z, r);
    gsl_blas_dtrsv(CblasUpper, CblasNoTrans, CblasNonUnit, M1, z);
    gsl_vector_memcpy(d, z);
    gsl_blas_ddot(z, r, &rho);

    temp = gsl_vector_calloc((*x_bar)->size);
    
    while ((k <= A->size1) || (rho > 1e-8)) {
        gsl_blas_dgemv(CblasNoTrans, 1.0, A, d, 0.0, temp);
        gsl_blas_ddot(d, temp, &dotprod);
        alpha = rho / dotprod;
        gsl_blas_daxpy(alpha, d, *x_bar);
        gsl_blas_dgemv(CblasNoTrans, 1.0, A, d, 0.0, temp);
        gsl_blas_daxpy(-alpha, temp, r);
        gsl_vector_memcpy(z, r);
        gsl_blas_dtrsv(CblasUpper, CblasNoTrans, CblasNonUnit, M1, z);
        gsl_blas_ddot(z, r, &dotprod);
        beta = dotprod / rho;
        gsl_blas_ddot(z, r, &rho);
        gsl_vector_memcpy(temp, d);
        gsl_vector_scale(temp, beta);
        gsl_vector_add(temp, z);
        gsl_vector_memcpy(d, temp);
        k++;
    }

    /* get the error statistics */
    gatherErrors(*x_bar, x, x_error, max_error);

    gsl_vector_free(temp);
    gsl_vector_free(z);
    gsl_vector_free(r);
    gsl_vector_free(d);
    
    return 0;
}
