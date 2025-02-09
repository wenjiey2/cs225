#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(HSLAPixel color1, HSLAPixel color2, Point center, unsigned width, unsigned height);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  HSLAPixel color1;
  HSLAPixel color2;
  Point center;
  unsigned width;
  unsigned height;
};

#endif
