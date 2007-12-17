/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <CUnit/CUnit.h>

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
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
    vector_t vec, vec_read;
    matrix_t mat_read;
    char *temp_file;

    vec.size = 2;
    initV(&vec);

    temp_file = tmpnam(NULL);
    
    CU_ASSERT_EQUAL(write(temp_file, NULL, &vec), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &vec_read), ILLEGAL_FORMAT);
}


void testWriteBoth()
{
    vector_t vec, vec_read;
    matrix_t mat, mat_read;
    char *temp_file;

    vec.size = 2;
    mat.r = 2;
    mat.c = 3;

    initV(&vec);
    initM(&mat);

    temp_file = tmpnam(NULL);

    CU_ASSERT_EQUAL(write(temp_file, &mat, &vec), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &vec_read), 0);

    CU_ASSERT_EQUAL(vec_read.size, vec.size);
    CU_ASSERT_EQUAL(mat_read.r, mat.r);
    CU_ASSERT_EQUAL(mat_read.c, mat.c);
}


void testWriteMatrix()
{
    vector_t vec_read;
    matrix_t mat, mat_read;
    char *temp_file;

    mat.r = 2;
    mat.c = 3;

    initM(&mat);

    temp_file = tmpnam(NULL);

    CU_ASSERT_EQUAL(write(temp_file, &mat, NULL), 0);
    CU_ASSERT_EQUAL(read(temp_file, &mat_read, &vec_read), ILLEGAL_FORMAT);
}
