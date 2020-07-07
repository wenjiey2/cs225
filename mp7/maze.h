/* Your code here! */
#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <map>
#include <queue>



class SquareMaze{
public:
  /**
   * Empty constructor
   **/
  SquareMaze();

  /**
   * This function makes a new SquareMaze of the given height and width, select
   * random walls to delete without creating a cycle, until there are no more
   * walls that could be deleted without creating a cycle.
   *
   * @param width	The width of the SquareMaze (number of cells)
   * @param height The height of the SquareMaze (number of cells)
   **/
  void makeMaze(int width, int height);

  /**
   * This function uses representation of the maze to determine whether it is
   * possible to travel in the given direction from the square at coordinates
   * (x,y).
   *
   * @param x	The x coordinate of the current cell
   * @param y The y coordinate of the current cell
   * @param dir The desired direction to move from the current cell
   * @return whether you can travel in the specified direction
   **/
  bool canTravel(int x, int y, int dir) const;

  /**
   * This function sets whether or not the specified wall exists.
   *
   * @param x	The x coordinate of the current cell
   * @param y The y coordinate of the current cell
   * @param dir Either 0 (right) or 1 (down), which specifies which wall to set
   *            (same as the encoding explained in canTravel). You only need to
   *            support setting the bottom and right walls of every square in
   *            the grid.
   * @param exists true if setting the wall to exist, false otherwise
   **/
  void setWall(int x, int y, int dir, bool exists);

  /**
   * This function elect the square in the bottom row with the largest distance
   * from the origin as the destination of the maze.
   *
   * @return a vector of directions taken to solve the maze
   **/
  vector<int> solveMaze();

  /**
   * This function draws the maze without the solution.
   *
   * @return a PNG of the unsolved SquareMaze
   **/
  cs225::PNG* drawMaze() const;

  /**
   * This function calls drawMaze, then solveMaze; it modifies the PNG from
   * drawMaze to show the solution vector and the exit.
   *
   * @return a PNG of the solved SquareMaze
   **/
  cs225::PNG* drawMazeWithSolution();

  void makeCreativeMaze(int width, int height);

  vector<int> solveCreativeMaze();

  cs225::PNG* drawCreativeMaze();

  cs225::PNG* drawCreativeMazeWithSolution();

private:
  // width of the maze
  int w;

  // height of the maze
  int h;

  // vector containing all rightWalls in order
  vector<bool> rightWalls;

  // vector containing all downWalls in order
  vector<bool> downWalls;

  // every cell of in the maze
  DisjointSets cells;

  // private helper function that clears the previous data
  void clear();
};

#endif
