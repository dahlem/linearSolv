/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GEN_TEST_H__
#define __GEN_TEST_H__


#include <CUnit/CUnit.h>


void registerTests();


void testRandSPD();
void testNotSymmetric();
void testZeroScale();
void testTooSmall();
void testSolv();


static CU_TestInfo test_gen[] = {
    { "testNotSymmetric", testNotSymmetric },
    { "testZeroScale", testZeroScale },
    { "testTooSmall", testTooSmall },
    { "testRandSPD", testRandSPD },
    { "testSolv", testSolv },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
    { "TestGen", NULL, NULL, test_gen },
    CU_SUITE_INFO_NULL,
};


#endif
