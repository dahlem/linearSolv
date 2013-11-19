/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __PRECONDITION_TEST_H__
#define __PRECONDITION_TEST_H__


#include <CUnit/CUnit.h>


void registerPreconditionTests();



void testPrecondition();


static CU_TestInfo test_precondition[] = {
    { "testPrecondition", testPrecondition },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo precondition_suites[] = {
    { "TestPrecondition", NULL, NULL, test_precondition },
    CU_SUITE_INFO_NULL,
};

#endif
