
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("tests/pacman.png");
  FloodFilledImage image(png);
  HSLAPixel color1(200, 1, 0.5);
  HSLAPixel color2(0, 1, 0.5);
  BFS bfs(png, Point(00, 50), 0.2);
  BFS dfs(png, Point(00, 50), 0.2);
  Point center(png.width() / 2, png.height() / 2);
  double width = 30;
  double height = 60;
  MyColorPicker mine(color1, color2, center, width, height);
  MyColorPicker mine2(color1, color2, center, height, width);
  image.addFloodFill(bfs, mine);
  image.addFloodFill(dfs, mine2);
  Animation animation = image.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");


  return 0;
}
