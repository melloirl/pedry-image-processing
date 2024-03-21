#include "distance.h"

float euclidean_distance(PixelCoordinates ip, PixelCoordinates fp){
  float x = (fp.x - ip.x) * (fp.x - ip.x);
  float y = (fp.y - ip.y) * (fp.y - ip.y);
  return sqrt(x + y);
}

float d4_distance(PixelCoordinates ip, PixelCoordinates fp){
  return fabs(fp.x - ip.x) + fabs(fp.y - ip.y);
}

float d8_distance(PixelCoordinates ip, PixelCoordinates fp){
  return fmax(fabs(fp.x - ip.x), fabs(fp.y - ip.y));
}
