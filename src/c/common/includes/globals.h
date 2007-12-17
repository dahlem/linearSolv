/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

/**
 * Declaration of global types.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GLOBALS_H__
#define __GLOBALS_H__


/**
 * a structure for an array and its size.
 */
typedef struct
{
    double *vector;
    int size;
} vector_t;

/**
 * a structure for a matrix and its dimensions.
 */
typedef struct
{
    double **matrix;
    double *_block;
    int r;
    int c;
} matrix_t;


void initM(matrix_t *mat);
void initV(vector_t *vec);
void freeM(matrix_t *mat);
void freeV(vector_t *vec);


#endif
