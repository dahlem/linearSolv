/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>

#include "linsolv-cl.h"

#include "matio.h"
#include "matgen.h"

#include "conjugate.h"
#include "gauss.h"
#include "chol.h"
#include "jacobi.h"
#include "lu.h"
#include "precondition.h"
#include "qr.h"
#include "seidel.h"
#include "steepest.h"
#include "subst.h"



int main(int argc, char *argv[])
{
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
    gsl_vector *x, *b, *x_bar, *x_error, *e;
    gsl_matrix *A;
    double maxError;
    size_t i, j;
    
    /* initialise and configure the command line options */
    init();
    process_cl(argc, argv);

    /* if a file was specified read the matrix and vectors from it */
    if (globalArgs.file != NULL) {
        read(globalArgs.file, &A, &x, &b);

        /* Invoke the respective solver */
        switch (globalArgs.s) {
          case 'g':
              gauss(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'l':
              lu(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'c':
              chol(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'j':
              jacobi(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 's':
              seidel(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'd':
              steepest(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'u':
              conjugate(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'p':
              precondition(A, b, x, &x_bar, &x_error, &maxError);
              break;
          case 'q':
              qr(A, b, x, &x_bar, &x_error, &maxError);
              break;
          default:
              fprintf(stderr, "Error: Solver %c is not known.\n\n", globalArgs.s);
              displayHelp();
              break;
        }

        printf("Results:\n");
        printf("Solution Vector x_bar:\n");
        for (i = 0; i < x_bar->size; ++i) {
            printf(" %f\n", gsl_vector_get(x_bar, i));
        }
        printf("\nError Vector x - x_bar:\n");
        for (i = 0; i < x_error->size; ++i) {
            printf(" %f\n", gsl_vector_get(x_error, i));
        }
        printf("Max error max|x - x_bar|:\n");
        printf(" %f\n\n", maxError);

        gsl_vector_free(x_bar);
        gsl_vector_free(x_error);
    } else {
        /* set up the random number generator */
        gsl_rng_env_setup();
        rng = gsl_rng_alloc(rng_type);

        /* generate a SPD matrix randomly and solve for x = [-1,...,-1] */
        linsolv(rng, globalArgs.n, 1.0, &A, &b);

        printf("\nGenerated Matrix A:\n");
        for (i = 0; i < A->size1; ++i) {
            for (j = 0; j < A->size2; ++j) {
                printf("%f, ", gsl_matrix_get(A, i, j));
            }
            printf("\n");
        }
        printf("Solution Vector b:\n\n");
        for (i = 0; i < b->size; ++i) {
            printf(" %f\n", gsl_vector_get(b, i));
        }

        /* write x = [-1,...,-1] */
        x = gsl_vector_calloc(b->size);
        gsl_vector_set_all(x, -1.0);
        
        if (globalArgs.o) {
            write("output.dat", A, x, b);
        }
    }

    /* if specified invoke the eigenvalue solver */
    if (globalArgs.e) {
        eigen(A, &e, 1e-6);

        printf("\nEigen Values lambda:\n");
        for (i = 0; i < e->size; ++i) {
            printf(" %f\n", gsl_vector_get(e, i));
        }

        gsl_vector_free(e);
    }

    gsl_vector_free(x);
    gsl_vector_free(b);
    gsl_matrix_free(A);
    
    return EXIT_SUCCESS;
}
