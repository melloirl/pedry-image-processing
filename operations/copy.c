#include "bmp.h"

void write_header(FILE *file, BMPHeader *header){
  fwrite(header, sizeof(BMPHeader), 1, file);
}

void write_dib_header(FILE *file, DIBHeader *dib_header) {
  fseek(file, sizeof(BMPHeader), SEEK_SET);
  fwrite(dib_header, sizeof(DIBHeader), 1, file);
}

void write_pixel_array(FILE *file, unsigned char *pixels, DIBHeader *dib_header) {
  if (dib_header->bits_count <= 8) {
    fseek(file, sizeof(BMPHeader) + dib_header->header_size + 1024, SEEK_SET);
    fwrite(pixels, dib_header->image_width * dib_header->image_height, 1, file);
  } else {
    fseek(file, sizeof(BMPHeader) + dib_header->header_size, SEEK_SET);
    fwrite(pixels, dib_header->image_width * dib_header->image_height, 3, file);
  }
  
}

void write_color_table(FILE *file, unsigned char *color_table, DIBHeader *dib_header) {
  fseek(file, sizeof(BMPHeader) + dib_header->header_size, SEEK_SET);
  fwrite(color_table, sizeof(unsigned char), 1024, file);
}

void copy(char *input, char *output) {
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
  write_pixel_array(output_file, pixels, dib_header);

  // Compare sizes of input and output files
  fseek(input_file, 0, SEEK_END);
  fseek(output_file, 0, SEEK_END);
  free(header);
  free(dib_header);
  free(color_table);
  free(pixels);
  fclose(input_file);
  fclose(output_file);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }
  copy(argv[1], argv[2]);
  return 0;
}
