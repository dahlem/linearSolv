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

#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
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
    matrix_t mat;

    mat.r = 100;
    mat.c = mat.r;

    initM(&mat);

    gsl_rng_env_setup();
    gsl_rng *rng = gsl_rng_alloc(rng_type);

    CU_ASSERT_EQUAL(randSPD(rng, 1.0, &mat), 0);

    freeM(&mat);
}
