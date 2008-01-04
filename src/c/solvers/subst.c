/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include "subst.h"



bool isUpper(gsl_matrix *M) 
{
    size_t i, j;

    if ((M->size1 + 1) != M->size2) {
        return false;
    }

    for (i = 0; i < M->size1; ++i) {
        for (j = 0; j < (M->size2 - 1); ++j) {
            if (j < i) {
                if (gsl_matrix_get(M, i, j) != 0) {
                    return false;
                }
            }
        }
    }

    return true;
}


/* int subst_backwards(gsl_matrix *M, gsl_vector **x_bar) */
/* { */
/* //    size_t i, j; */


/*     *x_bar = gsl_vector_calloc(M->size1); */

    
/*     return 0; */
/* } */
