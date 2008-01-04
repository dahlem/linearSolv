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

#include "subst.h"

#include "subst_test.h"


void registerSubstTests()
{
    if (CU_register_suites(subst_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testIsUpperWrongRowColumn()
{
    double a[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 3);

    CU_ASSERT_EQUAL(isUpper(&A.matrix), false);
}


void testIsNotUpper()
{
    double a[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 4, 3);

    CU_ASSERT_EQUAL(isUpper(&A.matrix), false);
}


void testIsUpper()
{
    double a[] = {
        1, 2, 3, 4,
        0, 6, 7, 8,
        0, 0, 11, 12
    };

    gsl_matrix_view A = gsl_matrix_view_array(a, 3, 4);

    CU_ASSERT_EQUAL(isUpper(&A.matrix), true);
}


void testBackwards()
{
    gsl_vector *x_bar;
    size_t i;

    double u[] = {
        1, 0.5, 1.5, 2, 5,
        0, 1, -1, 16, 16,
        0, 0, 1, -41, -40,
        0, 0, 0, 1, 1
    };

    gsl_matrix_view M = gsl_matrix_view_array(u, 4, 5);

    CU_ASSERT_EQUAL(subst_backwards(&M.matrix, &x_bar), 0);

    for (i = 0; i < x_bar->size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(
            gsl_vector_get(x_bar, i),
            1.0,
            0.01);
    }
}


void testForwards() 
{
    gsl_vector *x_bar;
    size_t i;

    double l[] = {
        2, 0, 0, 0, 2,
        3, -0.5, 0, 0, 2.5,
        2, 2, 1, 0, 5,
        1, 1.5, 4, 141, 147.5
    };

    gsl_matrix_view M = gsl_matrix_view_array(l, 4, 5);

    CU_ASSERT_EQUAL(subst_forwards(&M.matrix, &x_bar), 0);

    for (i = 0; i < x_bar->size; ++i) {
        CU_ASSERT_DOUBLE_EQUAL(
            gsl_vector_get(x_bar, i),
            1.0,
            0.01);
    }
}
