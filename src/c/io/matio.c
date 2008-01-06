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
#include <string.h>
#include <time.h>

#include "config.h"
#include "matio.h"




int skip(FILE * const file, int num_lines)
{
    int c;
    int lines = 0;


    while ((c = fgetc(file)) != EOF) {
        switch (c) {
          case '\n':
              lines++;
              break;
          default:
              break;
        }

        if (lines == num_lines) {
            return 0;
        }
    }

    return CANNOT_SKIP;
}


int write(const char * const filename, gsl_matrix *mat, gsl_vector *x, gsl_vector *b)
{
    FILE *out;
    char timestamp[128];
    time_t t;
    struct tm *time_now;
    size_t ret;
    unsigned int i, j;


    if ((out = fopen(filename, "w")) == NULL) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return COULD_NOT_READ_FILE;
    }

    t = time(NULL);
    time_now = localtime(&t);

    if (time_now != NULL) {
        ret = strftime(timestamp, sizeof(timestamp), "%a %b %d %H:%M:%S %Y %Z", time_now);
    }

    if (ret != 0) {
        fprintf(out, "# Created by %s, %s\n",
                PACKAGE_STRING,
                timestamp);
    } else {
        fprintf(out, "# Created by %s\n",
                PACKAGE_STRING);
    }

    if (mat != NULL) {
        fprintf(out, "# name: A\n");
        fprintf(out, "# type: matrix\n");
        fprintf(out, "# rows: %d\n", mat->size1);
        fprintf(out, "# columns: %d\n", mat->size2);

        for (i = 0; i < mat->size1; ++i) {
            for (j = 0; j < mat->size2; ++j) {
                fprintf(out, " %f", gsl_matrix_get(mat, i, j));
            }
            fprintf(out, "\n");
        }
    }

    if (x != NULL) {
        fprintf(out, "# name: v\n");
        fprintf(out, "# type: matrix\n");
        fprintf(out, "# rows: %d\n", x->size);
        fprintf(out, "# columns: 1\n");

        for (i = 0; i < x->size; ++i) {
            fprintf(out, " %f\n", gsl_vector_get(x, i));
        }
    }

    if (b != NULL) {
        fprintf(out, "# name: b\n");
        fprintf(out, "# type: matrix\n");
        fprintf(out, "# rows: %d\n", b->size);
        fprintf(out, "# columns: 1\n");

        for (i = 0; i < b->size; ++i) {
            fprintf(out, " %f\n", gsl_vector_get(b, i));
        }
    }

    fclose(out);

    return 0;
}


int read_dim(FILE * const file, int *rows, int *columns)
{
    char line[MAX_LINE_BUFFER];
    char line_tokens[2][3][MAX_TOKEN_BUFFER];
    int j;


    /* read a line and tokenise it into 3 expected parts */
    for (j = 0; j < 2; ++j) {
        if (fgets(line, MAX_LINE_BUFFER, file) == NULL) {
            return PREMATURE_END_OF_STREAM;
        }

        if (sscanf(line, "%s %s %s",
                   line_tokens[j][0],
                   line_tokens[j][1],
                   line_tokens[j][2]) != 3) {
            return PREMATURE_END_OF_STREAM;
        }
    }

    /* Expected line spec '# row/column: int' */
    if (strcmp(line_tokens[0][1], ROW_SPEC) == 0) {
        *rows = atoi(line_tokens[0][2]);
    } else if (strcmp(line_tokens[0][1], COL_SPEC) == 0) {
        *columns = atoi(line_tokens[0][2]);
    } else {
        return UNKNOWN_TOKEN;
    }

    if (strcmp(line_tokens[1][1], ROW_SPEC) == 0) {
        *rows = atoi(line_tokens[1][2]);
    } else if (strcmp(line_tokens[1][1], COL_SPEC) == 0) {
        *columns = atoi(line_tokens[1][2]);
    } else {
        return UNKNOWN_TOKEN;
    }

    return 0;
}

int readVector(FILE * const file, gsl_vector **vec)
{
    unsigned int i;
    float elem;
    

    for (i = 0; i < (*vec)->size; ++i) {
        if (fscanf(file, "%f", &elem) != 1) {
            return PREMATURE_END_OF_STREAM;
        }

        gsl_vector_set(*vec, i, elem);
    }

    return 0;
}


int readMatrix(FILE * const file, gsl_matrix **mat)
{
    unsigned int i, j;
    float elem;
    

    for (i = 0; i < (*mat)->size1; ++i) {
        for (j = 0; j < (*mat)->size2; ++j) {
            if (fscanf(file, "%f", &elem) != 1) {
                return PREMATURE_END_OF_STREAM;
            }
            gsl_matrix_set(*mat, i, j, elem);
        }
    }

    return 0;
}


int read(const char * const filename, gsl_matrix **mat, gsl_vector **x, gsl_vector **b)
{
    FILE *in;
    int ret, rows, columns;


    if ((in = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return COULD_NOT_READ_FILE;
    }

    if ((ret = skip(in, 3)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((ret = read_dim(in, &rows, &columns)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((rows > 0) && (columns > 1)) {
        *mat = gsl_matrix_calloc(rows, columns);
        readMatrix(in, mat);
    } else {
        return ILLEGAL_FORMAT;
    }

    if ((ret = skip(in, 3)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((ret = read_dim(in, &rows, &columns)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((rows > 0) && (columns == 1)) {
        *x = gsl_vector_alloc(rows);
        readVector(in, x);
    } else {
        return ILLEGAL_FORMAT;
    }

    if ((ret = skip(in, 3)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((ret = read_dim(in, &rows, &columns)) != 0) {
        return ILLEGAL_FORMAT;
    }

    if ((rows > 0) && (columns == 1)) {
        *b = gsl_vector_alloc(rows);
        readVector(in, b);
    } else {
        return ILLEGAL_FORMAT;
    }

    fclose(in);

    return 0;
}
