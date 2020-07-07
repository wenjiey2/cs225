#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image *i = new Image();
Image *i2 = new Image();
Image *i3 = new Image();
Image *i4 = new Image();
Image *i5 = new Image();
i->readFromFile("alma.png");
i2->readFromFile("utd.png");
i2->scale(200,200);
i3->readFromFile("wmmt5dx+.png");
i4->readFromFile("redsuns.png");
i4->scale(400,400);
StickerSheet *s = new StickerSheet(*i, 3);
s->addSticker(*i3, 50, 20);
s->addSticker(*i2, 400, 300);
s->addSticker(*i4, 10, 400);
*i5 = s->render();
i5->writeToFile("myImage.png");
delete i;
delete i2;
delete i3;
delete i4;
delete i5;
delete s;
  return 0;
}
