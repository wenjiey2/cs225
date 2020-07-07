#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;
int main()
{
    // Write your own main here
    SquareMaze m;
    m.makeCreativeMaze(50, 50);
    std::cout << "MakeMaze complete" << std::endl;

    PNG* creative = m.drawCreativeMazeWithSolution();
    creative->writeToFile("creative.png");
    delete creative;
    return 0;
}
