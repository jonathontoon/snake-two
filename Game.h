#ifndef GAME_H
#define GAME_H

#include <Arduboy2.h>
#include "Snake.h"
#include "Food.h"
#include "Maze.h"
#include "BonusItem.h"

extern Arduboy2 arduboy;

class Game {
private:
  Snake snake;
  Food food;
  Maze maze;
  BonusItem bonusItem;
  int score;
  int level;
  int bonusSpawnTimer;
  int bonusMultiplier;
  int consecutiveBonuses;
  bool gameOver;

public:
  Game();
  void reset();
  void handleInput();
  void update();
  void draw() const;
  bool isGameOver() const;
  void checkLevelAdvancement();
  void updateGameSpeed();
};

#endif