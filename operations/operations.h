#ifndef OPERATIONS_H
#define OPERATIONS_H

// Function declaration for convolution that accepts two float arrays and their sizes
float* convolution(float* input, int input_size, float* kernel, int kernel_size);
float* convolution_2d(float* input, int input_rows, int input_cols, float* kernel, int kernel_rows, int kernel_cols);

#endif // OPERATIONS_H
