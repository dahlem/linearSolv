/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __SUBST_TEST_H__
#define __SUBST_TEST_H__


#include <CUnit/CUnit.h>


void registerSubstTests();



void testIsUpperWrongRowColumn();
void testIsNotUpper();
void testIsUpper();
void testBackwards();
void testForwards();


static CU_TestInfo test_subst[] = {
    { "testIsUpperWrongRowColumn", testIsUpperWrongRowColumn },
    { "testIsNotUpper", testIsNotUpper },
    { "testIsUpper", testIsUpper },
    { "testBackwards", testBackwards },
    { "testForwards", testForwards },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo subst_suites[] = {
    { "TestSubst", NULL, NULL, test_subst },
    CU_SUITE_INFO_NULL,
};

#endif
