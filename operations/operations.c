  #include <stdlib.h>

  int output[ROWS][COLS];
int input[ROWS][COLS];
int kernel[KERNEL_ROWS][KERNEL_COLS];

  float* convolution(float* input, int input_size, float* kernel, int kernel_size){
      float* output = (float*)malloc((input_size + kernel_size - 1) * sizeof(float));
      for(int i = 0; i < input_size + kernel_size - 1; i++){
          output[i] = 0;
      }
      for(int i = 0; i < input_size; i++){
          for(int j = 0; j < kernel_size; j++){
              output[i + j] += input[i] * kernel[j];
          }
      }
      return output;
  }

  float* convolution_2d(float* input, int input_rows, int input_cols, float* kernel, int kernel_rows, int kernel_cols){
      float* output = (float*)malloc((input_rows + kernel_rows - 1) * (input_cols + kernel_cols - 1) * sizeof(float));
      for(int i = 0; i < (input_rows + kernel_rows - 1) * (input_cols + kernel_cols - 1); i++){
          output[i] = 0;
      }
      for(int i = 0; i < input_rows; i++){
          for(int j = 0; j < input_cols; j++){
              for(int k = 0; k < kernel_rows; k++){
                  for(int l = 0; l < kernel_cols; l++){
                      output[i + k][j + l] += input[i][j] * kernel[k][l];
                  }
              }
          }
      }
      return output;
  }
