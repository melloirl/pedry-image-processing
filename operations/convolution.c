#include "bmp.h"

int main(){
  FILE *file = open_file("./images/snail.bmp", "rb");
  unsigned char *pixels = get_pixel_array(file);
  // Print the first 10 pixels
  for (int i = 0; i < 10; i++) {
    printf("%d ", pixels[i]);
  }
  printf("\n");
  free(pixels);
  fclose(file);
  return 0;
}
