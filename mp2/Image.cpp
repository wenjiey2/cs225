#include "Image.h"
#include <cmath>

Image::Image(): PNG(){

}

Image::Image(unsigned int width, unsigned int height): PNG(width, height){

}

void Image::lighten(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.l + 0.1 > 1.0){
        pixel.l = 1.0;
      } else{
        pixel.l += 0.1;
      }
    }
  }
}

void Image::lighten(double amount){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.l + amount > 1.0){
        pixel.l = 1.0;
      } else{
        pixel.l += amount;
      }
    }
  }
}

void Image::darken(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.l - 0.1 < 0){
        pixel.l = 0;
      } else{
        pixel.l -= 0.1;
      }
    }
  }
}

void Image::darken(double amount){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.l - amount < 0){
        pixel.l = 0;
      } else{
        pixel.l -= amount;
      }
    }
  }
}

void Image::saturate(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.s + 0.1 > 1.0){
        pixel.s = 1.0;
      } else{
        pixel.s += 0.1;
      }
    }
  }
}

void Image::saturate (double amount){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.s + amount > 1.0){
        pixel.s = 1.0;
      } else{
        pixel.s += amount;
      }
    }
  }
}

void Image::desaturate(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.s - 0.1 < 0){
        pixel.s = 0;
      } else{
        pixel.s -= 0.1;
      }
    }
  }
}

void Image::desaturate (double amount){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
       HSLAPixel& pixel = this->getPixel(i,j);
      if(pixel.s - amount < 0){
        pixel.s = 0;
      } else{
        pixel.s -= amount;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor (double degrees){
  for (unsigned i = 0; i < this->width(); i++) {
    for (unsigned j = 0; j < this->height(); j++) {
      HSLAPixel & pixel = this->getPixel(i, j);
      double hue = pixel.h + degrees;
      while (hue >= 360){
        hue -= 360;
      }
      while (hue < 0){
        hue += 360;
      }
      pixel.h = hue;
    }
  }
}

void Image::illinify(){
  double oHue = 11;
  double bHue = 216;
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      double & pixelHue = this->getPixel(x, y).h;
      double oDifference = abs(pixelHue - oHue);
      double bDifference = abs(pixelHue - bHue);
      if(oDifference > 180){
        oDifference = 360 - oDifference;
      }
      if(bDifference > 180){
        bDifference = 360 - bDifference;
      }
      if (oDifference < bDifference) {
        pixelHue = oHue;
      } else if (oDifference > bDifference) {
        pixelHue = bHue;
      }
    }
  }
}

void Image::scale(double factor){
  Image * resized = new Image((unsigned int)(this->width() * factor), (unsigned int)(this->height() * factor));
  for (unsigned i = 0; i < this->width() * factor; i++) {
    for (unsigned j = 0; j < this->height() * factor; j++) {
      unsigned int newX = i / factor;
      unsigned int newY = j / factor;
      HSLAPixel & pixel = resized -> getPixel(i, j);
      pixel.h = this -> getPixel(newX, newY).h;
      pixel.l = this -> getPixel(newX, newY).l;
      pixel.a = this -> getPixel(newX, newY).a;
      pixel.s = this -> getPixel(newX, newY).s;
    }
  }
  *this = *resized;
  delete resized;
}

void Image::scale(unsigned w, unsigned h){
  double ratio;
  Image * resized;
  unsigned width = w;
  unsigned height = h;
  ratio = this -> width() / this -> height();
  if(w / h < ratio){
    height = w / ratio;
  } else {
    width = h * ratio;
  }
  resized = new Image(width, height);
  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < height; j++) {
      unsigned int newX = i * this -> width() / width ;
      unsigned int newY = j * this -> height() / height;
      HSLAPixel & pixel = resized -> getPixel(i, j);
      pixel.h = this -> getPixel(newX, newY).h;
      pixel.l = this -> getPixel(newX, newY).l;
      pixel.a = this -> getPixel(newX, newY).a;
      pixel.s = this -> getPixel(newX, newY).s;
    }
  }
  *this = *resized;
  delete resized;
}
