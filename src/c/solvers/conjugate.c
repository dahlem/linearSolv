/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
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

#include "conjugate.h"
#include "error.h"
#include "util.h"



int conjugate(gsl_matrix *A, gsl_vector *b, gsl_vector *x,
              gsl_vector **x_bar, gsl_vector **x_error, double *max_error)
{
    gsl_vector *r, *p, *temp;
    size_t k;
    double dp, dotprod, alpha, beta;
    

    if (b->size != A->size1) {
        return MATRIX_VECTOR_UNEQUAL_ROW_DIM;
    }
    
/*     if ((status = isPositiveDefinite(A))) { */
/*         return status; */
/*     } */

    *x_bar = gsl_vector_calloc(x->size);
    p = gsl_vector_calloc(x->size);
    r = gsl_vector_calloc(x->size);

    gsl_vector_memcpy(*x_bar, x);
    gsl_vector_memcpy(p, b);
    gsl_blas_dgemv(CblasNoTrans, -1.0, A, *x_bar, 1.0, p);
    gsl_vector_memcpy(r, p);
    alpha = beta = 0.0;
    k = 1;
    dp = gsl_blas_dnrm2(r) * gsl_blas_dnrm2(r);
    temp = gsl_vector_calloc((*x_bar)->size);
    
    while ((k <= A->size1) || (dp > 1e-12)) {
        gsl_blas_dgemv(CblasNoTrans, 1.0, A, p, 0.0, temp);
        gsl_blas_ddot(p, temp, &dotprod);
        alpha = dp / dotprod;
        gsl_blas_daxpy(alpha, p, *x_bar);
        gsl_blas_daxpy(-alpha, temp, r);
        beta = gsl_blas_dnrm2(r) * gsl_blas_dnrm2(r) / dp;
        gsl_vector_memcpy(temp, p);
        gsl_vector_scale(temp, beta);
        gsl_vector_add(temp, r);
        gsl_vector_memcpy(p, temp);
        dp = gsl_blas_dnrm2(r) * gsl_blas_dnrm2(r);
        k++;
    }

    gatherErrors(*x_bar, x, x_error, max_error);

    gsl_vector_free(temp);
    gsl_vector_free(p);
    gsl_vector_free(r);
    
    return 0;
}
