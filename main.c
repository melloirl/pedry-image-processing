#include "operations/operations.h"
#include <stdio.h>

int main() {
    float matrix[3][5] = {{120, 120, 120, 120, 120}, {120, 210, 120, 30, 120}, {120, 120, 120, 120, 120}};
    float mask[3][3] = {{1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}, {1.0/9, 1.0/9, 1.0/9}};

    float* result = convolution_2d((float*)matrix, 3, 5, (float*)mask, 3, 3);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 5; j++){
            printf("%f ", result[i * 5 + j]);
        }
        printf("\n");
    }

    return 0;
}
