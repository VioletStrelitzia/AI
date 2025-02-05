#ifndef _LINEAR_H_
#define _LINEAR_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "nn.h"

/**
 * @brief 线性层
 * 
 */
typedef struct Linear {
    int input_size, output_size;
    Float* output_data;
    Float* weight, *bias;
    Float* weightGard, *biasGard;
} Linear;

/**
 * @brief 初始化 Linear 层
 * 
 * @param linear 指向 Linear 实例的指针
 * @param input_size 输入向量的长度
 * @param output_size 输出向量的长度
 * @param requireGard 是否需要梯度
 */
void init_linear(
    Linear* const linear,
    int const input_size,
    int const output_size,
    bool const requireGard = false) {
    linear->output_data = (Float*)malloc(output_size * sizeof(Float));
    linear->weight = (Float*)malloc(input_size * output_size * sizeof(Float));
    linear->bias = (Float*)malloc(output_size * sizeof(Float));
    if (requireGard) {
        linear->weightGard = (Float*)malloc(input_size * output_size * sizeof(Float));
        linear->biasGard = (Float*)malloc(output_size * sizeof(Float));
    } else {
        linear->weightGard = linear->biasGard = NULL;
    }
}

void forward_linear(Linear* const linear, Float* const input_data) {
    // Wx + b
    // W_rows = output_size, W_cols = input_size
    memset(linear->output_data, 0, linear->output_size * sizeof(Float));
    Float* weight_ptr = linear->weight;
    for (int r = 0; r < linear->output_size; ++r) {
        for (int c = 0; c < linear->input_size; ++c, ++weight_ptr)
            linear->output_data[r] += *weight_ptr * input_data[c];
        linear->output_data[r] += linear->bias[r];
    }
}

/**
 * @brief 释放 Linear 的资源
 * 
 * @param linear 指向 Linear 实例的指针
 */
void free_linear(Linear* const linear) {
    free(linear->output_data);
    free(linear->weight);
    free(linear->bias);
    free(linear->weightGard);
    free(linear->biasGard);
}

#endif