/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __LU_TEST_H__
#define __LU_TEST_H__


#include <CUnit/CUnit.h>


void registerLUTests();



void testCrout();
void testLU();


static CU_TestInfo test_lu[] = {
    { "testCrout", testCrout },
    { "testLU", testLU },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo lu_suites[] = {
    { "TestLU", NULL, NULL, test_lu },
    CU_SUITE_INFO_NULL,
};

#endif
