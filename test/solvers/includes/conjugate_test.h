/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __CONJUGATE_TEST_H__
#define __CONJUGATE_TEST_H__


#include <CUnit/CUnit.h>


void registerConjugateTests();



void testConjugate();


static CU_TestInfo test_conjugate[] = {
    { "testConjugate", testConjugate },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo conjugate_suites[] = {
    { "TestConjugate", NULL, NULL, test_conjugate },
    CU_SUITE_INFO_NULL,
};

#endif
