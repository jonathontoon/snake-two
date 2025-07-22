#ifndef BONUSITEM_H
#define BONUSITEM_H

#include <Arduboy2.h>
#include "Point.h"

extern Arduboy2 arduboy;

// Forward declarations
class Snake;
class Maze;

class BonusItem {
private:
  GamePoint position;
  bool active;
  int lifespan;
  int maxLifespan;
  int points;

public:
  BonusItem();
  void spawn(const Snake& snake, const Maze& maze);
  void update();
  void draw() const;
  bool isActive() const;
  bool checkCollision(const GamePoint& point);
  int getPoints() const;
  void deactivate();
};

#endif