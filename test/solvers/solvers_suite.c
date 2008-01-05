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
#include <CUnit/Basic.h>

#include "conjugate_test.h"
#include "gauss_test.h"
#include "chol_test.h"
#include "jacobi_test.h"
#include "lu_test.h"
#include "precondition_test.h"
#include "seidel_test.h"
#include "steepest_test.h"
#include "subst_test.h"


int main (int argc, char* argv[])
{
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    registerSubstTests();
    registerGaussTests();
    registerLUTests();
    registerCholTests();
    registerJacobiTests();
    registerSeidelTests();
    registerSteepestTests();
    registerConjugateTests();
    registerPreconditionTests();
    
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
   
    return CU_get_error();
}
