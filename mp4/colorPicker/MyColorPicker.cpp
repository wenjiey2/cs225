#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double dx = x - center.x;
  double dy = y - center.y;
  double d = dx - width + dy - height;

  if (dx - width >= 1 &&  dy - height >= 1) { return color2; }

  double h = color1.h - (color1.h * d) + (color2.h * d);
  double s = color1.s - (color1.s * d) + (color2.s * d);
  double l = color1.l - (color1.l * d) + (color2.l * d);

  return HSLAPixel(h, s, l);
}

MyColorPicker::MyColorPicker(
  HSLAPixel color1, HSLAPixel color2, Point center, unsigned width, unsigned height
) : color1(color1), color2(color2), center(center), width(width), height(height) { }
