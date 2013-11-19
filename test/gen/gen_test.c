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
#include <gsl/gsl_rng.h>
#include <gsl/gsl_blas.h>

#include "matgen.h"
#include "gen_test.h"


void registerTests()
{
    if (CU_register_suites(suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}

void testRandSPD()
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_matrix *mat;
    gsl_rng *rng;
    size_t i, j;
    double abs_value;

    mat = gsl_matrix_calloc(10, 10);

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(randSPD(rng, 1.0, mat), 0);

    for (i = 0; i < mat->size1; ++i) {
        abs_value = 0.0;
        
        for (j = 0; j < mat->size2; ++j) {
            CU_ASSERT_DOUBLE_EQUAL(
                gsl_matrix_get(mat, i, j),
                gsl_matrix_get(mat, j, i),
                0.0001);
            if (i != j) {
                abs_value += abs(gsl_matrix_get(mat, i, j));
            }
        }

        CU_ASSERT_TRUE(abs_value < gsl_matrix_get(mat, i, i));
    }

    gsl_matrix_free(mat);
    free(rng);
}

void testZeroScale()
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_matrix *mat;

    mat = gsl_matrix_calloc(10, 10);

    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(randSPD(rng, 0, mat), ZERO_SCALE);

    gsl_matrix_free(mat);
    free(rng);
}

void testNotSymmetric()
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_matrix *mat;

    mat = gsl_matrix_calloc(10, 11);

    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(randSPD(rng, 1.0, mat), MATRIX_NOT_SYMMETRIC);

    gsl_matrix_free(mat);
    free(rng);
}

void testTooSmall()
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_matrix *mat;

    mat = gsl_matrix_calloc(1, 2);

    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(randSPD(rng, 1.0, mat), MATRIX_TOO_SMALL);

    gsl_matrix_free(mat);
    free(rng);
}

void testSolv() 
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_matrix *mat;
    gsl_vector *b, *x, *temp;
    size_t i;
    
    
    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(
        linsolv(rng, 10, 1.0, &mat, &b),
        0
        );

    x = gsl_vector_alloc(10);
    gsl_vector_set_all(x, -1.0);    
    temp = gsl_vector_calloc(10);
    gsl_blas_dgemv(CblasNoTrans, 1.0, mat, x, 0.0, temp);

    for (i = 0; i < temp->size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(
            gsl_vector_get(b, i),
            gsl_vector_get(temp, i),
            0.01);
    }

    gsl_matrix_free(mat);
    gsl_vector_free(b);
    gsl_vector_free(temp);
    free(rng);
}
