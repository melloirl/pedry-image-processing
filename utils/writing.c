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
