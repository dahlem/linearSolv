/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __STEEPEST_TEST_H__
#define __STEEPEST_TEST_H__


#include <CUnit/CUnit.h>


void registerSteepestTests();



void testSteepest();


static CU_TestInfo test_steepest[] = {
    { "testSteepest", testSteepest },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo steepest_suites[] = {
    { "TestSteepest", NULL, NULL, test_steepest },
    CU_SUITE_INFO_NULL,
};

#endif
