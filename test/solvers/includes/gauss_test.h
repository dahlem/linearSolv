/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GAUSS_TEST_H__
#define __GAUSS_TEST_H__


#include <CUnit/CUnit.h>


void registerGaussTests();



void testLargestPivot();
void testPivotRow();
void testPivotRowRowOutOfBounds();
void testPivotRowColOutOfBounds();
void testLargestPivotRowOutOfBounds();
void testLargestPivotColOutOfBounds();
void testTriangular();
void testGauss();


static CU_TestInfo test_gauss[] = {
    { "testLargestPivot", testLargestPivot },
    { "testLargestPivotRowOutOfBounds", testLargestPivotRowOutOfBounds },
    { "testLargestPivotColOutOfBounds", testLargestPivotColOutOfBounds },
    { "testPivotRow", testPivotRow },
    { "testPivotRowRowOutOfBounds", testPivotRowRowOutOfBounds },
    { "testPivotRowColOutOfBounds", testPivotRowColOutOfBounds },
    { "testTriangular", testTriangular },
    { "testGauss", testGauss },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo gauss_suites[] = {
    { "TestGauss", NULL, NULL, test_gauss },
    CU_SUITE_INFO_NULL,
};

#endif
