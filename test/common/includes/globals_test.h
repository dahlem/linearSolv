/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GLOBALS_TEST_H__
#define __GLOBALS_TEST_H__


#include <CUnit/CUnit.h>


void registerTests();



void testInitVector();


static CU_TestInfo test_global[] = {
    { "testInitVector", testInitVector },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo suites[] = {
    { "TestGlobals", NULL, NULL, test_global },
    CU_SUITE_INFO_NULL,
};

#endif
