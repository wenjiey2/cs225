/* Your code here! */
#include "maze.h"

using namespace cs225;
SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height) {
    // clear previous data
    clear();
    w = width;
    h = height;

    //initialize all cells
    cells.addelements(w * h);
    for(int i = 0; i < w * h; i++){
      rightWalls.push_back(true);
      downWalls.push_back(true);
    }

    // push all walls in a vector in order
    vector<tuple<int, int, int>> walls;
    for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
        if(i != width - 1){
          walls.push_back(tuple<int, int, int>(i, j, 0));
        }
        if(j != height - 1){
          walls.push_back(tuple<int, int, int>(i, j, 1));
        }
      }
    }

    random_shuffle(walls.begin(), walls.end());

    // iterate through random order of walls
    for(tuple<int, int, int> wall : walls){
      int x = get<0>(wall);
      int y = get<1>(wall);
      int dir = get<2>(wall);

      // calculate adjacent cell coordinates
      int adjX = x;
      int adjY = y;
      if (dir == 0){
        adjX++;
      } else if (dir == 1){
        adjY++;
      } else if (dir == 2){
        adjX--;
      } else if (dir == 3){
        adjY--;
      }

      // see if they are in the same set
      int idx = y * w + x;
      int adjIdx = adjY * w + adjX;
      if(cells.find(idx) != cells.find(adjIdx)) {
          setWall(x, y, dir, false);
          cells.setunion(idx, adjIdx);
      }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  if(dir == 0 && x < w - 1){
    return (!rightWalls[y * w + x]);
  } else if(dir == 1 && y < h - 1){
    return (!downWalls[y * w + x]);
  } else if(dir == 2 && x - 1 >= 0){
    return (!rightWalls[y * w + x - 1]);
  } else if(dir == 3 && y - 1 >= 0){
    return (!downWalls[(y - 1) * w + x]);
  } else {
    return false;
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int idx = y * w + x;
  if(dir == 0 && x < w - 1){
    if(exists){
      rightWalls[idx] = true;
    } else{
      rightWalls[idx] = false;
    }
  }
  if(dir == 1 && y < h - 1){
    if(exists){
      downWalls[idx] = true;
    } else{
      downWalls[idx] = false;
    }
  }
}

vector<int> SquareMaze::solveMaze(){

  //traverse through the maze
  map<int, int> maze;
  queue<int> q;
  int start = 0;
  q.push(start);
  maze[start] = -1;
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    int currCell = maze[curr];
    int x = curr % w;
    int y = curr / w;
    for (int i = 0; i < 4; i++) {
      int adjX = x;
      int adjY = y;
      if (i == 0){
        adjX++;
      } else if (i == 1){
        adjY++;
      } else if (i == 2){
        adjX--;
      } else if (i == 3){
        adjY--;
      }
      int adjCell = adjY * w + adjX;
      if(canTravel(x, y, i) && currCell != adjCell) {
        maze[adjCell] = curr;
        q.push(adjCell);
      }
    }
  }
  vector<int> longestPath = vector<int>();
  int y = h - 1;

  //find the exit that has the longest path to the origin
  //start from last row and find the path backwards
  for(int x = 0; x < w; x++){
    int end = y * w + x;
    vector<int> path;
    while (start != end){
    int currCell = maze[end];
    if(end - currCell == 1){
      path.push_back(0);
    } else if (end - currCell == w){
      path.push_back(1);
    } else if (end - currCell == -1) {
        path.push_back(2);
    } else if (end - currCell == -w) {
        path.push_back(3);
    }
    end = currCell;
    }
    if(path.size() > longestPath.size()){
      longestPath = path;
    }
  }

  //reverse the order of path
  reverse(longestPath.begin(), longestPath.end());
  return longestPath;
}


PNG* SquareMaze::drawMaze() const{
  PNG* maze = new PNG(w * 10 + 1, h * 10 + 1);

  // left vertical edge
	for(unsigned i = 0; i < maze->height(); i++){
		maze->getPixel(0, i).h = 0;
		maze->getPixel(0, i).s = 0;
		maze->getPixel(0, i).l = 0;
    maze->getPixel(0, i).a = 1;
	}

  // top horizontal edge except entrance (1,0) to (9,0)
  for(unsigned i = 10; i < maze->width(); i++){
		maze->getPixel(i, 0).h = 0;
		maze->getPixel(i, 0).s = 0;
		maze->getPixel(i, 0).l = 0;
    maze->getPixel(i, 0).a = 1;
	}

	for(int x = 0; x < w; x++){
    for(int y = 0; y < h; y++){
      int idx = y * w + x;
		  if(rightWalls[idx]){
			  for(int k = 0; k <= 10; k++){
          maze->getPixel((x + 1) * 10, y * 10 + k).h = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).s = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).l = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).a = 1;
        }
		  }
		  if(downWalls[idx]){
        for(int k = 0; k <= 10; k++){
          maze->getPixel(x * 10 + k, (y + 1) * 10).h = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).s = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).l = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).a = 1;
        }
		  }
	  }
  }
	return maze;
}

PNG* SquareMaze::drawMazeWithSolution(){
  PNG* maze = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;

  // draw the path from origin
	for(size_t i = 0; i < solution.size(); i++){
    if(solution[i] == 1){
  		for(int j = 0; j <= 10; j++){
  			maze->getPixel(x, y + j).h = 0;
  			maze->getPixel(x, y + j).s = 1;
  			maze->getPixel(x, y + j).l = 0.5;
        maze->getPixel(x, y + j).a = 1;
  	  }
  		y += 10;
  	} else if(solution[i] == 0){
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x + j, y).h = 0;
  			maze->getPixel(x + j, y).s = 1;
  			maze->getPixel(x + j, y).l = 0.5;
        maze->getPixel(x + j, y).a = 1;
			}
  	  x += 10;
  	} else if(solution[i] == 3){
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x , y - j).h = 0;
  			maze->getPixel(x, y - j).s = 1;
  			maze->getPixel(x, y - j).l = 0.5;
        maze->getPixel(x, y - j).a = 1;
  	  }
  	  y -= 10;
  	} else{
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x - j, y).h = 0;
        maze->getPixel(x - j, y).s = 1;
        maze->getPixel(x - j, y).l = 0.5;
        maze->getPixel(x - j, y).a = 1;
  	}
   		x -= 10;
  	}
  }

  // draw exit
  int exitX = x / 10;
	int exitY = h - 1;
	for(int k = 1; k <= 9; k++){
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).h = 0;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).s = 0;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).l = 1;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).a = 1;
  }
	return maze;
}

void SquareMaze::clear(){
  w = 0;
  h = 0;
  rightWalls.clear();
  downWalls.clear();
  cells.clearSet();
}

void SquareMaze::makeCreativeMaze(int width, int height) {
    // clear previous data
    clear();
    w = width;
    h = height;

    //initialize all cells
    cells.addelements(w * h);
    for(int i = 0; i < w * h; i++){
      rightWalls.push_back(true);
      downWalls.push_back(true);
    }


    // push all walls in a vector in order
    vector<tuple<int, int, int>> walls;
    for(int i = 0; i < w; i++){
      for(int j = 0; j < h; j++){
        if(i != width - 1){
          walls.push_back(tuple<int, int, int>(i, j, 0));
        }
        if(j != height - 1){
          walls.push_back(tuple<int, int, int>(i, j, 1));
        }
      }
    }

    random_shuffle(walls.begin(), walls.end());

    // iterate through random order of walls
    for(tuple<int, int, int> wall : walls){
      int x = get<0>(wall);
      int y = get<1>(wall);
      int dir = get<2>(wall);

      // calculate adjacent cell coordinates
      int adjX = x;
      int adjY = y;
      if (dir == 0){
        adjX++;
      } else if (dir == 1){
        adjY++;
      } else if (dir == 2){
        adjX--;
      } else if (dir == 3){
        adjY--;
      }

      // see if they are in the same set
      int idx = y * w + x;
      int adjIdx = adjY * w + adjX;
      if(y < h / 5 || (x > 2 * w / 5 && x < 3 * w / 5)){
        if(cells.find(idx) != cells.find(adjIdx)) {
          setWall(x, y, dir, false);
          cells.setunion(idx, adjIdx);
        }
      }
    }
}

vector<int> SquareMaze::solveCreativeMaze(){

  //traverse through the maze
  map<int, int> maze;
  queue<int> q;
  int start = 0;
  q.push(start);
  maze[start] = -1;
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    int currCell = maze[curr];
    int x = curr % w;
    int y = curr / w;
    for (int i = 0; i < 4; i++) {
      int adjX = x;
      int adjY = y;
      if (i == 0){
        adjX++;
      } else if (i == 1){
        adjY++;
      } else if (i == 2){
        adjX--;
      } else if (i == 3){
        adjY--;
      }
      int adjCell = adjY * w + adjX;
      if(canTravel(x, y, i) && currCell != adjCell) {
        maze[adjCell] = curr;
        q.push(adjCell);
      }
    }
  }
  vector<int> longestPath = vector<int>();
  int y = h - 1;

  //find the exit that has the longest path to the origin
  //start from last row and find the path backwards
  for(int x = 2 * w / 5; x < 3 * w / 5; x++){
    int end = y * w + x;
    vector<int> path;
    while (start != end){
    int currCell = maze[end];
    if(end - currCell == 1){
      path.push_back(0);
    } else if (end - currCell == w){
      path.push_back(1);
    } else if (end - currCell == -1) {
        path.push_back(2);
    } else if (end - currCell == -w) {
        path.push_back(3);
    }
    end = currCell;
    }
    if(path.size() > longestPath.size()){
      longestPath = path;
    }
  }

  //reverse the order of path
  reverse(longestPath.begin(), longestPath.end());
  return longestPath;
}

PNG* SquareMaze::drawCreativeMaze(){
  PNG* maze = new PNG(w * 10 + 1, h * 10 + 1);

  // left vertical edges
	for(unsigned i = 0; i < maze->height() / 5; i++){
		maze->getPixel(0, i).h = 0;
		maze->getPixel(0, i).s = 0;
		maze->getPixel(0, i).l = 0;
    maze->getPixel(0, i).a = 1;
	}

  for(unsigned i = maze->height() / 5; i < maze->height(); i++){
		maze->getPixel(2 * maze->width() / 5, i).h = 0;
		maze->getPixel(2 * maze->width() / 5, i).s = 0;
		maze->getPixel(2 * maze->width() / 5, i).l = 0;
    maze->getPixel(2 * maze->width() / 5, i).a = 1;
	}

  // right vertical edges
	for(unsigned i = 0; i < maze->height() / 5; i++){
		maze->getPixel(maze->width() - 1, i).h = 0;
		maze->getPixel(maze->width() - 1, i).s = 0;
		maze->getPixel(maze->width() - 1, i).l = 0;
    maze->getPixel(maze->width() - 1, i).a = 1;
	}

  for(unsigned i = maze->height() / 5; i < maze->height(); i++){
		maze->getPixel(3 * maze->width() / 5, i).h = 0;
		maze->getPixel(3 * maze->width() / 5, i).s = 0;
		maze->getPixel(3 * maze->width() / 5, i).l = 0;
    maze->getPixel(3 * maze->width() / 5, i).a = 1;
	}


  // horizontal edge
  for(unsigned i = 0; i < 2 * maze->width() / 5; i++){
		maze->getPixel(i, maze->height() / 5).h = 0;
		maze->getPixel(i, maze->height() / 5).s = 0;
		maze->getPixel(i, maze->height() / 5).l = 0;
    maze->getPixel(i, maze->height() / 5).a = 1;
	}

  for(unsigned i = 3 * maze->width() / 5; i < maze->width(); i++){
		maze->getPixel(i, maze->height() / 5).h = 0;
		maze->getPixel(i, maze->height() / 5).s = 0;
		maze->getPixel(i, maze->height() / 5).l = 0;
    maze->getPixel(i, maze->height() / 5).a = 1;
	}

  // top horizontal edge except entrance (1,0) to (9,0)
  for(unsigned i = 10; i < maze->width(); i++){
		maze->getPixel(i, 0).h = 0;
		maze->getPixel(i, 0).s = 0;
		maze->getPixel(i, 0).l = 0;
    maze->getPixel(i, 0).a = 1;
	}

	for(int x = 0; x < w; x++){
    for(int y = 0; y < h / 5; y++){
      int idx = y * w + x;
		  if(rightWalls[idx]){
			  for(int k = 0; k <= 10; k++){
          maze->getPixel((x + 1) * 10, y * 10 + k).h = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).s = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).l = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).a = 1;
        }
		  }
		  if(downWalls[idx]){
        for(int k = 0; k <= 10; k++){
          maze->getPixel(x * 10 + k, (y + 1) * 10).h = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).s = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).l = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).a = 1;
        }
		  }
	  }
  }

  for(int x = 2 * w / 5; x < 3 * w / 5; x++){
    for(int y = h / 5; y < h; y++){
      int idx = y * w + x;
		  if(rightWalls[idx]){
			  for(int k = 0; k <= 10; k++){
          maze->getPixel((x + 1) * 10, y * 10 + k).h = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).s = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).l = 0;
          maze->getPixel((x + 1) * 10, y * 10 + k).a = 1;
        }
		  }
		  if(downWalls[idx]){
        for(int k = 0; k <= 10; k++){
          maze->getPixel(x * 10 + k, (y + 1) * 10).h = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).s = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).l = 0;
          maze->getPixel(x * 10 + k, (y + 1) * 10).a = 1;
        }
		  }
	  }
  }
	return maze;
}

PNG* SquareMaze::drawCreativeMazeWithSolution(){
  PNG* maze = drawCreativeMaze();
  vector<int> solution = solveCreativeMaze();
  int x = 5;
  int y = 5;

  // draw the path from origin
	for(size_t i = 0; i < solution.size(); i++){
    if(solution[i] == 1){
  		for(int j = 0; j <= 10; j++){
  			maze->getPixel(x, y + j).h = 0;
  			maze->getPixel(x, y + j).s = 1;
  			maze->getPixel(x, y + j).l = 0.5;
        maze->getPixel(x, y + j).a = 1;
  	  }
  		y += 10;
  	} else if(solution[i] == 0){
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x + j, y).h = 0;
  			maze->getPixel(x + j, y).s = 1;
  			maze->getPixel(x + j, y).l = 0.5;
        maze->getPixel(x + j, y).a = 1;
			}
  	  x += 10;
  	} else if(solution[i] == 3){
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x , y - j).h = 0;
  			maze->getPixel(x, y - j).s = 1;
  			maze->getPixel(x, y - j).l = 0.5;
        maze->getPixel(x, y - j).a = 1;
  	  }
  	  y -= 10;
  	} else{
  		for(int j = 0; j <= 10; j++){
        maze->getPixel(x - j, y).h = 0;
        maze->getPixel(x - j, y).s = 1;
        maze->getPixel(x - j, y).l = 0.5;
        maze->getPixel(x - j, y).a = 1;
  	}
   		x -= 10;
  	}
  }

  // draw exit
  int exitX = x / 10;
	int exitY = h - 1;
	for(int k = 1; k <= 9; k++){
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).h = 0;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).s = 0;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).l = 1;
    maze->getPixel(exitX * 10 + k, (exitY + 1) * 10).a = 1;
  }
  return maze;
}
