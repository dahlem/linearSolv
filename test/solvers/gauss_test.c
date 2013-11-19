/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
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

#include "gauss.h"

#include "gauss_test.h"


void registerGaussTests()
{
    if (CU_register_suites(gauss_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testLargestPivot()
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(largestPivot(&A.matrix, 0, 1), 1);
}


void testLargestPivotRowOutOfBounds() 
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(largestPivot(&A.matrix, 3, 1), ROW_OUT_OF_BOUNDS);
}


void testLargestPivotColOutOfBounds() 
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(largestPivot(&A.matrix, 0, 4), COLUMN_OUT_OF_BOUNDS);
}


void testPivotRow() 
{
    size_t i;
    gsl_vector *temp;
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    temp = gsl_vector_alloc((&A.matrix)->size2);
    
    gsl_matrix_get_row(temp, &A.matrix, 0);

    CU_ASSERT_EQUAL(pivotRow(&A.matrix, 0, 1), 0);

    for (i = 0; i < temp->size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(
            gsl_vector_get(temp, i),
            gsl_matrix_get(&A.matrix, 1, i),
            0.001);
    }

    gsl_vector_free(temp);
}


void testPivotRowRowOutOfBounds() 
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(pivotRow(&A.matrix, 3, 1), ROW_OUT_OF_BOUNDS);
}


void testPivotRowColOutOfBounds() 
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(pivotRow(&A.matrix, 0, 4), COLUMN_OUT_OF_BOUNDS);
}


void testTriangular() 
{
    size_t i, j;
    double a[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(triangular(&A.matrix), 0);

    for (j = 0; j < ((&A.matrix)->size2 - 2); ++j) {
        for (i = (j + 1); i < (&A.matrix)->size1; ++i) {
            CU_ASSERT_DOUBLE_EQUAL(
                gsl_matrix_get(&A.matrix, i, j),
                0.0,
                0.001
                );
        }
    }
}


void testGauss() 
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

    CU_ASSERT_EQUAL(gauss(&A.matrix, &b.vector, &x.vector,
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
