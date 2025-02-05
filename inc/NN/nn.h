#ifndef _NN_H_
#define _NN_H_
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef float Float;

void print_matrix(Float* matrix, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            printf("%f ", matrix[r * cols + c]);
        }
        printf("\n");
    }
}

void matmul(
    Float* mat_left,
    Float* mat_right,
    Float* mat_dst,
    int rows_left,
    int cols_left,
    int cols_right) {
    memset(mat_dst, 0, rows_left * cols_right * sizeof(Float));
    for (int r = 0; r < rows_left; ++r) {
        for (int c = 0; c < cols_right; ++c) {
            for (int i = 0; i < cols_left; ++i) {
                *mat_dst += mat_left[r * cols_left + i] * mat_right[i * cols_right + c];
                //printf("%f, %f, %f\n", mat_left[r * cols_left + i], mat_right[i * cols_right + c], *mat_dst);
            }
            ++mat_dst;
        }
    }
}

#endif