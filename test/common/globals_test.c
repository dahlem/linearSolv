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
#include "globals_test.h"


void registerTests()
{
    if (CU_register_suites(suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testInitVector()
{
    int i = 0;
    vector_t vec;
    vec.size = 2;

    initV(&vec);

    CU_ASSERT_PTR_NOT_NULL(vec.vector);
    
    for (i = 0; i < vec.size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(vec.vector[i], 0.0, 0.0001);
    }
}


void testInitMatrix()
{
    int i,j = 0;
    matrix_t mat;
    mat.r = 2;
    mat.c = 3;

    initM(&mat);

    CU_ASSERT_PTR_NOT_NULL(mat.matrix);
    CU_ASSERT_PTR_NOT_NULL(mat._block);
    
    for (i = 0; i < mat.r; ++i) {
        for (j = 0; j < mat.c; ++j) {
            CU_ASSERT_DOUBLE_EQUAL(mat.matrix[i][j], 0.0, 0.0001);
        }
    }
}
