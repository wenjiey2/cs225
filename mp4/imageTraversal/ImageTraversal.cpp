#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  image = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal *i){
  image = i;
  current = i->peek();
  png = image->getPNG();
  start = image->getStart();
  tolerance = image->getTolerance();
  visited = new bool*[png.width()];
  for (unsigned int x = 0; x < png.width(); x++){
    visited[x] = new bool[png.height()];
    for (unsigned int y = 0; y < png.height(); y++){
      visited[x][y] = false;
    }
  }
  image->add(start);
}

void ImageTraversal::Iterator::setSurrPixels(){
  HSLAPixel startPixel = png.getPixel(start.x, start.y);
  if (start.x + 1 <= png.width()){
    HSLAPixel right = png.getPixel(start.x + 1, start.y);
    if (calculateDelta(startPixel, right) >= tolerance){//prevent traversal to right
      visited[start.x + 1][start.y] = true;
    }
    else {
      image->add(Point());
    }
  }
  if (start.y >= 1){
    HSLAPixel down = png.getPixel(start.x, start.y - 1);
    if (calculateDelta(startPixel, down) >= tolerance){//down
      visited[start.x][start.y - 1] = true;
    }
  }
  if (start.x >= 1){
    HSLAPixel left = png.getPixel(start.x - 1, start.y);
    if (calculateDelta(startPixel, left) >= tolerance){//left
      visited[start.x - 1][start.y] = true;
    }
  }
  if (start.y + 1 <= png.height()){
    HSLAPixel up = png.getPixel(start.x, start.y + 1);
    if (calculateDelta(startPixel, up) >= tolerance){//up
      visited[start.x][start.y + 1] = true;
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point temp = image->pop();

  visited[temp.x][temp.y] = true;//set current point to visited

  HSLAPixel startPixel = png.getPixel(start.x, start.y);

  if (temp.x + 1 < png.width()){//check in bound right pixel
    if (visited[temp.x + 1][temp.y] == false){//check visited
      HSLAPixel right = png.getPixel(temp.x + 1, temp.y);
      if (calculateDelta(startPixel, right) < tolerance){//check tolerance
        image->add(Point(temp.x + 1,temp.y));
      }
      else {
        visited[temp.x + 1][temp.y] = true;
      }
    }
  }

  if (temp.y + 1 < png.height()){//check in bound down pixel
  if (visited[temp.x][temp.y + 1] == false){//check visited
    HSLAPixel down = png.getPixel(temp.x, temp.y + 1);
    if (calculateDelta(startPixel, down) < tolerance){//check tolerance
      image->add(Point(temp.x,temp.y + 1));
    }
    else {
      visited[temp.x][temp.y + 1] = true;
    }
  }
}  //end of down pixel if


if (temp.x > 0){//check in bound left pixel
  if (visited[temp.x - 1][temp.y] == false){//check visited
    HSLAPixel left = png.getPixel(temp.x - 1, temp.y);
    if (calculateDelta(startPixel, left) < tolerance){//check tolerance
      image->add(Point(temp.x - 1,temp.y));
    }
    else {
      visited[temp.x - 1][temp.y] = true;
    }
  }
}//end of left pixel if

if (temp.y > 0){//check in bound up pixel
  if (visited[temp.x][temp.y - 1] == false){//check visited
    HSLAPixel up = png.getPixel(temp.x, temp.y - 1);
    if (calculateDelta(startPixel, up) < tolerance){//check tolerance
      image->add(Point(temp.x,temp.y - 1));
    }
    else {
      visited[temp.x][temp.y - 1] = true;
    }
  }
}//end of up pixel if

Point ref = image->peek();

while((visited[ref.x][ref.y] == true) && (image->empty() == false)){
  ref = image->pop();
  if (image->empty() == false) ref = image->peek();
}
return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return image->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool empty = false;
	bool otherEmpty = false;
  if(image == NULL){
    empty = true;
  }
  if(other.image == NULL){
    otherEmpty = true;
  }
  if(!empty){
    empty = image->empty();
  }
  if(!otherEmpty){
    otherEmpty = other.image->empty();
  }
  if(empty && otherEmpty){
    return false;
  } else if((!empty)&&(!otherEmpty)){
    return (image != other.image);
  } else{
    return true;
  }
}
