#ifndef POINT_H
#define POINT_H

#include <Arduboy2.h>

const int GRID_SIZE = 8;
const int SNAKE_MAX_LENGTH = 64;
const int GRID_WIDTH = WIDTH / GRID_SIZE;
const int GRID_HEIGHT = HEIGHT / GRID_SIZE;

struct GamePoint {
  int x, y;
  GamePoint(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

#endif