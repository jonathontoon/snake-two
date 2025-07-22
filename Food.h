#ifndef FOOD_H
#define FOOD_H

#include <Arduboy2.h>
#include "Point.h"

extern Arduboy2 arduboy;
extern const int GRID_SIZE;

// Forward declarations
class Snake;
class Maze;

class Food {
private:
  GamePoint position;

public:
  Food();
  void generate();
  void generateValidPosition(const Snake& snake);
  void generateValidPosition(const Snake& snake, const Maze& maze);
  GamePoint getPosition() const;
  void draw() const;
};

#endif