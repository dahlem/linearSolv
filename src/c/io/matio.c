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
#include "globals.h"
#include "matio.h"




int skip(FILE *file, int num_lines)
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


int write(const char *filename, matrix_t *mat, vector_t *vec)
{
    FILE *out;
    char timestamp[128];
    time_t t;
    struct tm *time_now;
    size_t ret;
    int i, j;


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
        if ((mat->matrix != NULL) && (mat->_block != NULL)) {
            fprintf(out, "# name: A\n");
            fprintf(out, "# type: matrix\n");
            fprintf(out, "# rows: %d\n", mat->r);
            fprintf(out, "# columns: %d\n", mat->c);

            for (i = 0; i < mat->r; ++i) {
                for (j = 0; j < mat->c; ++j) {
                    fprintf(out, " %f", mat->matrix[i][j]);
                }
                fprintf(out, "\n");
            }
        }
    }

    if (vec != NULL) {
        if (vec->vector != NULL) {
            fprintf(out, "# name: v\n");
            fprintf(out, "# type: matrix\n");
            fprintf(out, "# rows: %d\n", vec->size);
            fprintf(out, "# columns: 1\n");

            for (i = 0; i < vec->size; ++i) {
                fprintf(out, " %f\n", vec->vector[i]);
            }
        }
    }

    fclose(out);

    return 0;
}


int read_dim(const FILE *file, int *rows, int *columns)
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

int readVector(const FILE const* file, vector_t *vec)
{
    int i;

    for (i = 0; i < vec->size; ++i) {
        if (fscanf(file, "%f", &(vec->vector[i])) != 1) {
            return PREMATURE_END_OF_STREAM;
        }
    }

    return 0;
}


int readMatrix(const FILE const* file, matrix_t *mat)
{
    int i, j;

    for (i = 0; i < mat->r; ++i) {
        for (j = 0; j < mat->c; ++j) {
            if (fscanf(file, "%f", &(mat->matrix[i][j])) != 1) {
                return PREMATURE_END_OF_STREAM;
            }
        }
    }

    return 0;
}


int read(const char *filename, matrix_t *mat, vector_t *vec)
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
        mat->r = rows;
        mat->c = columns;
        initM(mat);
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
        vec->size = rows;
        initV(vec);
        readVector(in, vec);
    } else {
        return ILLEGAL_FORMAT;
    }

    fclose(in);

    return 0;
}
