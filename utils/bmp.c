#include <stdlib.h>
#include "bmp.h"

/* BMP utilities to facilitate the reading and writing of BMP files

A BMP is composed of the following parts
1. BMP header - 14 bytes
2. DIB header - 40 bytes
3. Pixel data - remaining bytes 

A BMP header contains the following parts:
1. Signature - 2 bytes
2. File size - 4 bytes
3. Reserved - 4 bytes
4. Data offset - 4 bytes 

The BMP Header is mostly used to check if the file is a BMP file and to get the offset to the pixel data.
After reading the BMP header, we can read the DIB header and the pixel data.

The DIB header contains the following parts:
1. Header size - 4 bytes
2. Image width - 2 bytes
3. Image height - 2 bytes
4. Planes - 2 bytes
5. Bits per pixel - 2 bytes

These sizes vary depending on the type of DIB header. 
The most common type is the BITMAPINFOHEADER which has a size of 40 bytes.
*/

/** Opens and returns a file pointer to the given file.
 *
 * @param filename The name of the file to open.
 * @param mode The mode to open the file in.
 * @return A file pointer to the opened file.
 */

FILE *open_file(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    perror("Error opening file");
    exit(1);
  }
  return file;
}

/**
 * Reads the BMP header from the given file.
 *
 * @param file The file to read from.
 * @param header Pointer to the BMPHeader structure to store the read header.
 */
void read_header(FILE *file, BMPHeader *header) {
  fread(header, sizeof(BMPHeader), 1, file);
  printf("BMP Header\n");
  printf("Signature: %c%c\n", header->signature[0], header->signature[1]);
  printf("File size: %u\n", header->file_size);
  printf("Reserved 1: %u\n", header->reserved1);
  printf("Reserved 2: %u\n", header->reserved2);
  printf("Data offset: %u\n", header->data_offset);
}

void read_dib_header(FILE *file, DIBHeader *header) {
  fseek(file, sizeof(BMPHeader), SEEK_SET);
  fread(header, sizeof(DIBHeader), 1, file); 
  printf("DIB Header\n");
  printf("Header size: %u\n", header->header_size);
  printf("Image width: %d\n", header->image_width);
  printf("Image height: %d\n", header->image_height);
  printf("Planes: %u\n", header->planes);
  printf("Bits per pixel: %u\n", header->bits_count);
  printf("Compression: %u\n", header->compression);
  printf("Image size: %u\n", header->image_size);
  printf("X pixels per meter: %d\n", header->x_pixels_per_meter);
  printf("Y pixels per meter: %d\n", header->y_pixels_per_meter);
  printf("Colors used: %u\n", header->colors_used);
  printf("Important colors: %u\n", header->important_colors);
}

BMPHeader *get_bmp_header(FILE *file) {
  BMPHeader *header = malloc(sizeof(BMPHeader));
  fread(header, sizeof(BMPHeader), 1, file);
  return header;
}

DIBHeader *get_dib_header(FILE *file) {
  DIBHeader *header = malloc(sizeof(DIBHeader));
  fseek(file, sizeof(BMPHeader), SEEK_SET);
  fread(header, sizeof(DIBHeader), 1, file);
  return header;
}

unsigned char *get_pixel_array(FILE *file, BMPHeader *header, DIBHeader *dib_header) {
    // Reset file position to the beginning
    fseek(file, 0, SEEK_SET);
    // Get the sizes for the BMP and DIB headers and possibly the color table
    int bmp_header_size = sizeof(BMPHeader);
    int dib_header_size = sizeof(DIBHeader);
    int color_table_size = 0;
    if (dib_header->bits_count <= 8) {
        color_table_size = 1024;
    }
    // Calculate the offset to the pixel data
    int data_offset = bmp_header_size + dib_header_size + color_table_size;
    // Allocate memory for the pixel data
    unsigned char *pixels = malloc(header->file_size - data_offset);
    // Read the pixel data
    fseek(file, data_offset, SEEK_SET);
    fread(pixels, header->file_size - data_offset, 1, file);
    return pixels;
}

int get_image_size(DIBHeader *header) {
  return header->image_width * header->image_height;
}

unsigned char *get_color_table(FILE *file, BMPHeader *header, DIBHeader *dib_header) {
  // Get the bit depth from the header
  int bit_depth = dib_header->bits_count;
  // If the value of the bit depth is less than or equal to 8, then the image has a color table
  if (bit_depth <= 8) {
    // Allocate memory for the color table
    // First, get the file size from the header
    int file_size = header->file_size;
    // Also get the data offset from the header
    int data_offset = header->data_offset;
    // Considering the color table comes right after the DIB header, we can calculate the size of the color table
    int color_table_size = data_offset - sizeof(BMPHeader) - sizeof(DIBHeader);
    // Allocate memory for the color table
    unsigned char *color_table = malloc(color_table_size);
    // Read the color table
    fseek(file, sizeof(BMPHeader) + sizeof(DIBHeader), SEEK_SET);
    fread(color_table, color_table_size, 1, file);
    return color_table;
  }
  return NULL;
}

void read_image(const char *filename) {
  FILE *file = open_file(filename, "rb");
  BMPHeader header;
  read_header(file, &header);
  DIBHeader dib_header;
  read_dib_header(file, &dib_header);
  fclose(file);
}

void read_segment_sizes(const char *filename) {
  FILE *file = open_file(filename, "rb");
  BMPHeader header;
  header = *get_bmp_header(file);
  DIBHeader dib_header;
  dib_header = *get_dib_header(file);
  unsigned char *color_table = get_color_table(file, &header, &dib_header);
  unsigned char *pixels = get_pixel_array(file, &header, &dib_header);
  printf("BMP Header size: %ld bytes\n", sizeof(BMPHeader));
  printf("DIB Header size: %ld bytes\n", sizeof(DIBHeader));
  printf("Pixel array size: %d bytes\n", get_image_size(&dib_header));
  if (color_table) {
    printf("Color table size: 1024 bytes\n");
  }
  printf("Total size: %d bytes\n", header.file_size);
  fclose(file);
}

