#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
  PNG image;
  image.readFromFile(inputFile);
  for (unsigned i = 0; i < image.width(); i++) {
    for (unsigned j = 0; j < image.height()/2; j++) {
      HSLAPixel * pixel1 = image.getPixel(i, j);
      HSLAPixel * pixel2 = image.getPixel(i, image.height()-j-1);
      HSLAPixel pixel3 = * pixel1;
      * pixel1 = * pixel2;
      * pixel2 = pixel3;
    }
  }
  for (unsigned i = 0; i < image.height(); i++) {
    for (unsigned j = 0; j < image.width()/2; j++) {
      HSLAPixel * pixel1 = image.getPixel(j, i);
      HSLAPixel * pixel2 = image.getPixel(image.width()-j-1, i);
      HSLAPixel pixel3 = * pixel1;
      * pixel1 = * pixel2;
      * pixel2 = pixel3;
    }
  }
image.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // Part 3
  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < height; j++) {
      HSLAPixel * pixel = png.getPixel(i, j);
      unsigned distance = sqrt((i - width / 2) * (i - width / 2) + (j - height / 2) *
      (j - height / 2));
      pixel->s = 1;
      pixel->l = 0.5;
      pixel->a = 1;
      if(distance < width / 16) {
        pixel->h = 0;
      } else if(distance < width / 8) {
        pixel->h = 25;
      } else if (distance < width / 5) {
        pixel->h = 50;
      } else if (distance < width / 3) {
        pixel->h = 100;
      } else if (distance < width / 2) {
        pixel->h = 220;
      } else {
        pixel->h = 310;
      }
      }
  }
  return png;
}
