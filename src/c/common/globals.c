/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdlib.h>
#include <string.h>

#include "globals.h"


void initM(matrix_t *mat)
{
    int dim = (*mat).r * (*mat).c;
    int i = 0;
    
    
    /* allocate memory for the block */
    (*mat)._block = malloc(dim * sizeof(double));
    memset((*mat)._block, 0, dim * sizeof(double));

    /* allocate the row pointers */
    (*mat).matrix = malloc((*mat).r * sizeof(double*));

    for (i = 0; i < mat->r; ++i) {
        (*mat).matrix[i] = &(*mat)._block[mat->c * i];
    }
}


void initV(vector_t *vec) 
{
    (*vec).vector = malloc((*vec).size * sizeof(double));
    memset((*vec).vector, 0, (*vec).size * sizeof(double));
}
