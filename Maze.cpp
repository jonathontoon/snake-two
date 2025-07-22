#include "Maze.h"

Maze::Maze() {
  clearLevel();
}

void Maze::clearLevel() {
  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
      obstacles[x][y] = false;
    }
  }
}

void Maze::loadLevel(int level) {
  clearLevel();
  
  switch (level) {
    case 1: // Simple border walls
      for (int x = 2; x < GRID_WIDTH - 2; x++) {
        addObstacle(x, 2);
        addObstacle(x, GRID_HEIGHT - 3);
      }
      for (int y = 2; y < GRID_HEIGHT - 2; y++) {
        addObstacle(2, y);
        addObstacle(GRID_WIDTH - 3, y);
      }
      break;
      
    case 2: // Cross pattern
      for (int i = 1; i < GRID_WIDTH - 1; i++) {
        addObstacle(i, GRID_HEIGHT / 2);
      }
      for (int i = 1; i < GRID_HEIGHT - 1; i++) {
        addObstacle(GRID_WIDTH / 2, i);
      }
      break;
      
    default: // No obstacles for level 0
      break;
  }
}

bool Maze::isObstacle(int x, int y) const {
  if (x < 0 || x >= GRID_WIDTH || y < 0 || y >= GRID_HEIGHT) {
    return false;
  }
  return obstacles[x][y];
}

void Maze::addObstacle(int x, int y) {
  if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
    obstacles[x][y] = true;
  }
}

void Maze::draw() const {
  for (int x = 0; x < GRID_WIDTH; x++) {
    for (int y = 0; y < GRID_HEIGHT; y++) {
      if (obstacles[x][y]) {
        arduboy.fillRect(x * GRID_SIZE, y * GRID_SIZE, 
                         GRID_SIZE - 1, GRID_SIZE - 1, WHITE);
      }
    }
  }
}