#ifndef IMAGE_BLUR_H
#define IMAGE_BLUR_H

#include <stdio.h>
#include <stdlib.h>

// Define the kernel size for the blur operation
#define KERNEL_SIZE 5

// Function to create a blurring kernel
float** create_kernel();

// Function to apply a blur effect to a grayscale BMP image
void blur_grey(char *input, char *output);

#endif // IMAGE_BLUR_H
