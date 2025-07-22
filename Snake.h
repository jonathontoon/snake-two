#ifndef SNAKE_H
#define SNAKE_H

#include <Arduboy2.h>
#include "Point.h"

extern Arduboy2 arduboy;
extern const int GRID_SIZE;
extern const int SNAKE_MAX_LENGTH;

class Snake {
private:
  GamePoint body[64]; // Using constant since SNAKE_MAX_LENGTH not available here
  int length;
  Direction dir;

public:
  Snake();
  void setDirection(Direction newDir);
  GamePoint getHead() const;
  int getLength() const;
  GamePoint getBodySegment(int index) const;
  void move();
  void applyWraparound();
  void grow();
  bool checkSelfCollision() const;
  void draw() const;
};

#endif