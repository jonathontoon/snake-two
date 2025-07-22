#ifndef MAZE_H
#define MAZE_H

#include <Arduboy2.h>
#include "Point.h"

extern Arduboy2 arduboy;

class Maze {
private:
  bool obstacles[16][8]; // Grid to track obstacle positions
  
public:
  Maze();
  void loadLevel(int level);
  bool isObstacle(int x, int y) const;
  void draw() const;
  void clearLevel();
  void addObstacle(int x, int y);
};

#endif