/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <gsl/gsl_linalg.h>

#include "util.h"



int isPositiveDefinite(gsl_matrix *A)
{
    gsl_matrix *temp;

    temp = gsl_matrix_alloc(A->size1, A->size2);
    
    if (gsl_linalg_cholesky_decomp(temp) == GSL_EDOM) {
        gsl_matrix_free(temp);
        return MATRIX_NOT_POS_DEF;
    }

    gsl_matrix_free(temp);
    
    return 0;
}
