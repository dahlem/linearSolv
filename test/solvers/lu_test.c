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

#include "lu.h"

#include "lu_test.h"


void registerLUTests()
{
    if (CU_register_suites(lu_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testCrout() 
{
    gsl_matrix *L, *U;
    size_t i, j;
    
    double a_array[] = {
        2, 1, 3, 4,
        3, 1, 5, -2,
        2, 3, 2, -5,
        1, 2, 4, 3
    };

    double l_array[] = {
        2, 0, 0, 0,
        3, -0.5, 0, 0,
        2, 2, 1, 0,
        1, 1.5, 4, 141
    };

    double u_array[] = {
        1, 0.5, 1.5, 2,
        0, 1, -1, 16,
        0, 0, 1, -41,
        0, 0, 0, 1
    };

    gsl_matrix_view A = gsl_matrix_view_array(a_array, 4, 4);
    gsl_matrix_view L_test = gsl_matrix_view_array(l_array, 4, 4);
    gsl_matrix_view U_test = gsl_matrix_view_array(u_array, 4, 4);

    CU_ASSERT_EQUAL(crout(&A.matrix, &L, &U), 0);
    
    for (i = 0; i < (&A.matrix)->size1; ++i) {
        for (j = 0; j < (&A.matrix)->size2; ++j) {
            CU_ASSERT_DOUBLE_EQUAL(
                gsl_matrix_get(&L_test.matrix, i, j),
                gsl_matrix_get(L, i, j),
                0.01);
            CU_ASSERT_DOUBLE_EQUAL(
                gsl_matrix_get(&U_test.matrix, i, j),
                gsl_matrix_get(U, i, j),
                0.01);
        }
    }

    gsl_matrix_free(L);
    gsl_matrix_free(U);
}
