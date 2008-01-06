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
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

#include "matio.h"

#include "io_test.h"


void registerTests()
{
    if (CU_register_suites(suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testWriteVector()
{
    gsl_matrix *mat_read;
    gsl_vector *x, *x_read, *b_read;
    char *temp_file;

    x = gsl_vector_calloc(2);

    temp_file = tmpnam(NULL);
    
    CU_ASSERT_EQUAL(write(temp_file, NULL, x, NULL), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &x_read, &b_read), ILLEGAL_FORMAT);

    gsl_vector_free(x);
}


void testWriteAll()
{
    gsl_vector *x, *x_read, *b, *b_read;
    gsl_matrix *mat, *mat_read;
    char *temp_file;

    x = gsl_vector_calloc(2);
    b = gsl_vector_calloc(2);
    mat = gsl_matrix_calloc(2, 3);

    temp_file = tmpnam(NULL);

    CU_ASSERT_EQUAL(write(temp_file, mat, x, b), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &x_read, &b_read), 0);

    CU_ASSERT_EQUAL(x_read->size, x->size);
    CU_ASSERT_EQUAL(b_read->size, b->size);
    CU_ASSERT_EQUAL(mat_read->size1, mat->size1);
    CU_ASSERT_EQUAL(mat_read->size2, mat->size2);

    gsl_vector_free(x);
    gsl_vector_free(b);
    gsl_matrix_free(mat);
    gsl_vector_free(x_read);
    gsl_vector_free(b_read);
    gsl_matrix_free(mat_read);
}


void testWriteMatrix()
{
    gsl_vector *x_read, *b_read;
    gsl_matrix *mat, *mat_read;
    char *temp_file;

    mat = gsl_matrix_calloc(2, 3);

    temp_file = tmpnam(NULL);

    CU_ASSERT_EQUAL(write(temp_file, mat, NULL, NULL), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &x_read, &b_read), ILLEGAL_FORMAT);

    gsl_matrix_free(mat);
}
