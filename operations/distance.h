#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct PixelCoordinates {
  float x;
  float y;
} PixelCoordinates;

float euclidean_distance(PixelCoordinates ip, PixelCoordinates fp);
float d4_distance(PixelCoordinates ip, PixelCoordinates fp);
float d8_distance(PixelCoordinates ip, PixelCoordinates fp);

#endif // DISTANCE_H
