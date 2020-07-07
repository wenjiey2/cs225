#include "StickerSheet.h"
#include "Image.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  num_ = max;
  base_ = new Image();
  *base_ = picture;
  image_ = new Image * [num_];
  x_ = new int[num_];
  y_ = new int[num_];
  for(unsigned i = 0; i < num_; i++){
    image_[i] = new Image();
    x_[i] = 0;
    y_[i] = 0;
  }
}

StickerSheet::~StickerSheet(){
  _clear();
}

StickerSheet::StickerSheet(const StickerSheet &other){
  _copy(other);
}

const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  if(this != &other){
    this->_clear();
    this->_copy(other);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
  if(num_ > max){
    for(unsigned i = max; i < num_; i++){
      if(image_[i]->width() != 0 && image_[i]->height() != 0){
        delete image_[i];
      }
    }
    num_ = max;
  } else if(num_ < max){
    Image ** enlarged = new Image * [max];
    for(unsigned i = 0; i < max; i++){
      enlarged[i] = new Image();
    }
    for(unsigned i = 0; i < num_; i++){
      *enlarged[i] = *image_[i];
      delete image_[i];
      image_[i] = NULL;
    }
    image_ = enlarged;
    num_ = max;
  }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  int index = -1;
  for(unsigned i = 0; i < num_; i++){
      if(image_[i]->width() == 0 && image_[i]->height() == 0){
        index = i;
        *image_[i] = sticker;
        break;
      }
  }
  if(index != -1){
    x_[index] = x;
    y_[index] = y;
  }
  return index;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(image_[index]->width() != 0 && image_[index]->height() != 0){
    x_[index] = x;
    y_[index] = y;
    return true;
  }
  return false;
}

void StickerSheet::removeSticker(unsigned index){
  if((index < num_) && image_[index]->width() != 0 && image_[index]->height() != 0){
    Image * empty = new Image();
    *image_[index] = *empty;
    delete empty;
    empty = NULL;
    x_[index] = 0;
    y_[index] = 0;
  }
}

Image * StickerSheet::getSticker(unsigned index) const{
  if(index < num_ && image_[index]->width() != 0 && image_[index]->height() != 0){
    return this->image_[index];
  }
  return NULL;
}

Image StickerSheet::render() const{
  unsigned int layerWidth = base_->width();
  unsigned int layerHeight = base_->height();
  for(unsigned i = 0; i < num_; i++){
    unsigned int width = x_[i] + image_[i]->width();
		unsigned int height = y_[i] + image_[i]->height();
    if (width > layerWidth){
      layerWidth = width;
    }
		if (height > layerHeight){
			layerHeight = height;
    }
  }
  Image render (layerWidth, layerHeight);
  for(unsigned i = 0; i < base_->width(); i++){
    for(unsigned j = 0; j < base_->height(); j++){
      render.getPixel(i,j) = base_->getPixel(i,j);
    }
  }
  for(unsigned i = 0; i < num_; i++){
    for(unsigned j = x_[i]; j < image_[i]->width() + x_[i]; j++){
      for(unsigned k = y_[i]; k < image_[i]->height() + y_[i]; k++){
        if(image_[i]->getPixel(j - x_[i], k - y_[i]).a != 0){
          render.getPixel(j,k) = image_[i]->getPixel(j - x_[i], k - y_[i]);
        }
      }
    }
  }
  return render;
}

void StickerSheet::_clear(){
  for(unsigned i = 0; i < num_; i++) {
    delete image_[i];
    image_[i] = NULL;
  }
  delete[] image_;
  image_ = NULL;
  delete base_;
  base_ = NULL;
  delete[] x_;
  x_ = NULL;
  delete[] y_;
  y_ = NULL;
}

void StickerSheet::_copy(const StickerSheet & other){
  num_ = other.num_;
  base_ = new Image();
  *base_ = *other.base_;
  image_ = new Image * [num_];
  x_ = new int[num_];
  y_ = new int[num_];
  for(unsigned i = 0; i < num_; i++){
    image_[i] = new Image();
    *image_[i] = *other.image_[i];
    x_[i] = other.x_[i];
    y_[i] = other.y_[i];
  }
}
