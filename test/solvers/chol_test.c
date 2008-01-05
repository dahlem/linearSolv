/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>

#include "chol.h"

#include "chol_test.h"


void registerCholTests()
{
    if (CU_register_suites(chol_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testCholCrout() 
{
    gsl_matrix *L, *LL;
    size_t i, j;
    
    double a_array[] = {
        1.86279, 0.47863, -0.54877,
        0.47863, 1.61609, 0.10628,
        -0.54877, 0.10628, 2.76115
    };

    gsl_matrix_view A = gsl_matrix_view_array(a_array, 3, 3);

    CU_ASSERT_EQUAL(cholcrout(&A.matrix, &L), 0);

    LL = gsl_matrix_calloc(3, 3);
    gsl_blas_dgemm(CblasNoTrans, CblasTrans, 1.0, L, L, 0.0, LL);
    
    for (i = 0; i < (&A.matrix)->size1; ++i) {
        for (j = 0; j < (&A.matrix)->size2; ++j) {
            CU_ASSERT_DOUBLE_EQUAL(
                gsl_matrix_get(LL, i, j),
                gsl_matrix_get(&A.matrix, i, j),
                0.01);
        }
    }

    gsl_matrix_free(L);
    gsl_matrix_free(LL);
}


void testChol()
{
    gsl_vector *x_bar, *x_error, *temp;
    double max_error;
    size_t i;
    
    double a_array[] = {
        1.86279, 0.47863, -0.54877,
        0.47863, 1.61609, 0.10628,
        -0.54877, 0.10628, 2.76115
    };

    double b_array[] = {
        1, 2, 3
    };
    
    double x_array[] = {
        1, 1, 1
    };
    
    gsl_matrix_view A = gsl_matrix_view_array(a_array, 3, 3);
    gsl_vector_view b = gsl_vector_view_array(b_array, 3);
    gsl_vector_view x = gsl_vector_view_array(x_array, 3);

    CU_ASSERT_EQUAL(chol(&A.matrix, &b.vector, &x.vector,
                         &x_bar, &x_error, &max_error), 0);

    temp = gsl_vector_calloc(x_bar->size);
    gsl_blas_dgemv(CblasNoTrans, 1.0, &A.matrix, x_bar, 0.0, temp);

    for (i = 0; i < temp->size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(
            gsl_vector_get(&b.vector, i),
            gsl_vector_get(temp, i),
            0.01);
    }

    gsl_vector_free(temp);
    gsl_vector_free(x_bar);
    gsl_vector_free(x_error);
}
