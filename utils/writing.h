#ifndef WRITING_H
#define WRITING_H

#include <stdio.h>
#include "bmp.h" 

// Function declarations

/**
 * Writes the BMP header to a file.
 * @param file Pointer to the file where the header will be written.
 * @param header Pointer to the BMPHeader structure to write.
 */
void write_header(FILE *file, BMPHeader *header);

/**
 * Writes the DIB header to a file.
 * @param file Pointer to the file where the header will be written.
 * @param dib_header Pointer to the DIBHeader structure to write.
 */
void write_dib_header(FILE *file, DIBHeader *dib_header);

/**
 * Writes the pixel array to a file.
 * @param file Pointer to the file where the pixels will be written.
 * @param pixels Pointer to the array of pixels.
 * @param dib_header Pointer to the DIBHeader structure.
 */
void write_pixel_array(FILE *file, unsigned char *pixels, DIBHeader *dib_header);

/**
 * Writes the color table to a file.
 * @param file Pointer to the file where the color table will be written.
 * @param color_table Pointer to the color table array.
 * @param dib_header Pointer to the DIBHeader structure.
 */
void write_color_table(FILE *file, unsigned char *color_table, DIBHeader *dib_header);

#endif
