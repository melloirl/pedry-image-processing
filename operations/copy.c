#include "../utils/bmp.h"
#include "../utils/writing.h"

void copy(char *input, char *output) {
  FILE *input_file = open_file(input, "rb");
  printf("Input file: %s\n", input);
  printf("Output file: %s\n", output);
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

