#include "../utils/bmp.h"
#include "../utils/writing.h"

// Declare kernel size and value configuration

#define KERNEL_SIZE 5
#define v 1.0 / (KERNEL_SIZE * KERNEL_SIZE)

float** create_kernel() {
    float** kernel = malloc(KERNEL_SIZE * sizeof(float*));
    for (int i = 0; i < KERNEL_SIZE; i++) {
        kernel[i] = malloc(KERNEL_SIZE * sizeof(float));
        for (int j = 0; j < KERNEL_SIZE; j++) {
            kernel[i][j] = v;
        }
    }
    return kernel;
}

void blur_grey(char *input, char *output) {
  FILE *input_file = open_file(input, "rb");
  FILE *output_file = open_file(output, "wb");

  BMPHeader *header = get_bmp_header(input_file);
  DIBHeader *dib_header = get_dib_header(input_file);
  unsigned char *color_table = get_color_table(input_file, header, dib_header);
  unsigned char *pixels = get_pixel_array(input_file, header, dib_header);

  write_header(output_file, header);
  write_dib_header(output_file, dib_header);
  if (color_table) {
    printf("Writing color table\n");
    write_color_table(output_file, color_table, dib_header);
  }

  float** kernel = create_kernel();

  // Apply the kernel to the image
  for (int i = 0; i < dib_header->image_height; i++) {
    for (int j = 0; j < dib_header->image_width; j++) {
      int sum = 0;
      for (int k = 0; k < KERNEL_SIZE; k++) {
        for (int l = 0; l < KERNEL_SIZE; l++) {
          int x = i + k - 1;
          int y = j + l - 1;
          if (x >= 0 && x < dib_header->image_height && y >= 0 && y < dib_header->image_width) {
            sum += pixels[x * dib_header->image_width + y] * kernel[k][l];
          }
        }
      }
      pixels[i * dib_header->image_width + j] = sum;
    }
  }

  write_pixel_array(output_file, pixels, dib_header);

  fseek(input_file, 0, SEEK_END);
  fseek(output_file, 0, SEEK_END);
  free(header);
  free(dib_header);
  free(color_table);
  free(pixels);
  fclose(input_file);
  fclose(output_file);
}
