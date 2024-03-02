// Contents of bmp.h as previously defined
#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct BMPHeader {
  uint8_t signature[2];
  uint32_t file_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t data_offset;
} BMPHeader;

typedef struct DIBHeader {
  uint32_t header_size;
  int32_t image_width;
  int32_t image_height;
  uint16_t planes;
  uint16_t bits_count;
  uint32_t compression;
  uint32_t image_size;
  int32_t x_pixels_per_meter;
  int32_t y_pixels_per_meter;
  uint32_t colors_used;
  uint32_t important_colors;
} DIBHeader;

#pragma pack(pop)

// Function prototypes
FILE *open_file(const char *filename, const char *mode);
void read_header(FILE *file, BMPHeader *header);
void read_dib_header(FILE *file, DIBHeader *header);
BMPHeader *get_bmp_header(FILE *file);
DIBHeader *get_dib_header(FILE *file);
unsigned char *get_pixel_array(FILE *file, BMPHeader *header, DIBHeader *dib_header);
int get_image_size(DIBHeader *header);
void read_image(const char *filename);
unsigned char *get_color_table(FILE *file, BMPHeader *header, DIBHeader *dib_header);
void read_segment_sizes(const char *filename);

#endif // BMP_H
