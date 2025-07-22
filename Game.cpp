#include "Game.h"

Game::Game() : score(0), level(0), bonusSpawnTimer(0), bonusMultiplier(1), consecutiveBonuses(0), gameOver(false) {}

void Game::reset() {
  snake = Snake();
  food = Food();
  bonusItem = BonusItem();
  maze.loadLevel(level);
  food.generateValidPosition(snake, maze);
  score = 0;
  bonusSpawnTimer = 200; // Wait 200 frames before first bonus
  bonusMultiplier = 1;
  consecutiveBonuses = 0;
  gameOver = false;
}

void Game::handleInput() {
  if (arduboy.justPressed(UP_BUTTON)) snake.setDirection(UP);
  if (arduboy.justPressed(RIGHT_BUTTON)) snake.setDirection(RIGHT);
  if (arduboy.justPressed(DOWN_BUTTON)) snake.setDirection(DOWN);
  if (arduboy.justPressed(LEFT_BUTTON)) snake.setDirection(LEFT);
}

void Game::update() {
  if (gameOver) return;

  snake.move();
  snake.applyWraparound();

  // Update bonus item
  bonusItem.update();
  
  // Handle bonus item spawning
  bonusSpawnTimer--;
  if (bonusSpawnTimer <= 0 && !bonusItem.isActive()) {
    if (random(100) < 30) { // 30% chance to spawn
      bonusItem.spawn(snake, maze);
    }
    bonusSpawnTimer = 150; // Reset timer
  }

  GamePoint head = snake.getHead();

  // Check maze collision
  if (maze.isObstacle(head.x, head.y)) {
    gameOver = true;
    return;
  }

  // Check self collision
  if (snake.checkSelfCollision()) {
    gameOver = true;
    return;
  }

  // Check bonus item collision
  if (bonusItem.checkCollision(head)) {
    consecutiveBonuses++;
    bonusMultiplier = 1 + (consecutiveBonuses / 3); // Multiplier increases every 3 bonuses
    int bonusPoints = bonusItem.getPoints() * bonusMultiplier * (level + 1);
    score += bonusPoints;
  }
  
  // Check food collision
  GamePoint foodPos = food.getPosition();
  if (head.x == foodPos.x && head.y == foodPos.y) {
    int foodPoints = 1 * (level + 1); // More points on higher levels
    score += foodPoints;
    snake.grow();
    consecutiveBonuses = 0; // Reset bonus streak when eating regular food
    bonusMultiplier = 1;
    checkLevelAdvancement();
    updateGameSpeed();
    food.generateValidPosition(snake, maze);
  }
}

void Game::draw() const {
  if (!gameOver) {
    maze.draw();
    snake.draw();
    food.draw();
    bonusItem.draw();
    
    arduboy.setCursor(0, 0);
    arduboy.print("Score: ");
    arduboy.print(score);
    arduboy.print(" L");
    arduboy.print(level);
  } else {
    arduboy.setCursor(32, 24);
    arduboy.print("GAME OVER");
    arduboy.setCursor(32, 32);
    arduboy.print("Score: ");
    arduboy.print(score);
    arduboy.setCursor(24, 48);
    arduboy.print("Press A to restart");
  }
}

bool Game::isGameOver() const {
  return gameOver;
}

void Game::checkLevelAdvancement() {
  int newLevel = score / 5; // Advance level every 5 points
  if (newLevel > level && newLevel <= 2) { // Max level 2
    level = newLevel;
    maze.loadLevel(level);
    food.generateValidPosition(snake, maze);
  }
}

void Game::updateGameSpeed() {
  // Increase frame rate based on score (max 12 FPS)
  int baseFrameRate = 8;
  int speedBonus = score / 10; // Increase by 1 FPS every 10 points
  int newFrameRate = baseFrameRate + speedBonus;
  if (newFrameRate > 12) newFrameRate = 12; // Cap at 12 FPS
  
  arduboy.setFrameRate(newFrameRate);
}