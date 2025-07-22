#include "Food.h"
#include "Snake.h"
#include "Maze.h"

Food::Food() {
  generate();
}

void Food::generate() {
  position.x = random(GRID_WIDTH);
  position.y = random(GRID_HEIGHT);
}

void Food::generateValidPosition(const Snake& snake) {
  bool validPosition = false;
  while (!validPosition) {
    generate();
    
    validPosition = true;
    for (int i = 0; i < snake.getLength(); i++) {
      GamePoint segment = snake.getBodySegment(i);
      if (segment.x == position.x && segment.y == position.y) {
        validPosition = false;
        break;
      }
    }
  }
}

void Food::generateValidPosition(const Snake& snake, const Maze& maze) {
  bool validPosition = false;
  while (!validPosition) {
    generate();
    
    validPosition = true;
    
    // Check if position conflicts with snake
    for (int i = 0; i < snake.getLength(); i++) {
      GamePoint segment = snake.getBodySegment(i);
      if (segment.x == position.x && segment.y == position.y) {
        validPosition = false;
        break;
      }
    }
    
    // Check if position conflicts with maze obstacles
    if (validPosition && maze.isObstacle(position.x, position.y)) {
      validPosition = false;
    }
  }
}

GamePoint Food::getPosition() const {
  return position;
}

void Food::draw() const {
  arduboy.fillRect(position.x * GRID_SIZE, position.y * GRID_SIZE, 
                   GRID_SIZE - 1, GRID_SIZE - 1, WHITE);
}