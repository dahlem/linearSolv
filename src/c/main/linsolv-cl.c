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
#include <unistd.h>

#include "linsolv-cl.h"


/**
 * getopt configuration of the command-line parameters.
 * All command-line arguments are optional.
 */
static const char *cl_arguments = "uh?f:s:en:o";



void displayHelp()
{
    printf("linsolvmain - solve a linear system.\n");
    printf(" -? : This help message.\n");
    printf(" -h : This help message.\n");
    printf(" -f : The file specifying the matrix and vectors.\n");
    printf("      Either -f or -n have to be specified.\n");
    printf(" -s : The solver to be chosen (select either one of:.\n");
    printf("      Gaussian elimination with scaling and pivoging (g);\n");
    printf("      LU decomposition using Crout reduction (l - <el>);\n");
    printf("      Cholesky decomposition using Cholesky-Crout reduction (c);\n");
    printf("      Jacobi iteration (j);\n");
    printf("      Gauss-Seidel iteration (s);\n");
    printf("      Method of steepest descent (d);\n");
    printf("      Conjugate Gradient method (u);\n");
    printf("      Jacobi pre-conditioned conjugate gradient method (p).\n");
    printf(" -e : Calculate the eigenvalues using QR decomposition.\n");
    printf(" -n : The dimension for the randomly generated matrix.\n");
    printf(" -o : Output the generated matrix into a file.\n");

    exit(EXIT_SUCCESS);
}


void init()
{
    globalArgs.n = DEFAULT_N;
    globalArgs.file = DEFAULT_FILE;
    globalArgs.s = DEFAULT_SOLVER;
    globalArgs.e = DEFAULT_EIGEN;
    globalArgs.o = DEFAULT_OUTPUT;
}


/**
 * Verify the command line arguments and check that they are consistent with each
 * other.
 */
void verify_cl() 
{
    if ((globalArgs.file == NULL) && (globalArgs.n == 0)) {
        fprintf(stderr, "Error: Either a file with the linear system specification or");
        fprintf(stderr, "the dimension N of a randomly generated matrix have to be");
        fprintf(stderr, "specified on the command-line.\n\n");
        displayHelp();
    }

    switch (globalArgs.s) {
      case 'g':
          break;
      case 'l':
          break;
      case 'c':
          break;
      case 'j':
          break;
      case 's':
          break;
      case 'd':
          break;
      case 'u':
          break;
      case 'p':
          break;
      default:
          fprintf(stderr, "Error: Solver %c is not known.\n\n", globalArgs.s);
          displayHelp();
          break;
    }

    if (globalArgs.file != NULL) {
        if (globalArgs.n > 0) {
            fprintf(stderr, "Notice: The parameter -n is ignored.\n\n");
        }
    } else {
        if (globalArgs.n <= 0) {
            fprintf(stderr, "Error: The parameter -n has to be positive.\n\n");
            displayHelp();
        }
    }
}


void process_cl(int argc, char **argv)
{
    int opt = 0;

    opt = getopt(argc, argv, cl_arguments);

    while (opt != -1) {
        switch (opt) {
            case 'f':
                globalArgs.file = optarg;
                break;
            case 's':
                globalArgs.s = optarg[0];
                break;
            case 'e':
                globalArgs.e = true;
                break;
            case 'n':
                globalArgs.n = atoi(optarg);
                break;
            case 'o':
                globalArgs.o = true;
                break;
            case 'h':
            case '?':
                 displayHelp();
                 break;
            default:
                 break;
        }
        opt = getopt(argc, argv, cl_arguments);
    }

    verify_cl();
}
