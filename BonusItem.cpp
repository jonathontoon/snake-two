#include "BonusItem.h"
#include "Snake.h"
#include "Maze.h"

BonusItem::BonusItem() : active(false), lifespan(0), maxLifespan(120), points(5) {
  position = GamePoint(0, 0);
}

void BonusItem::spawn(const Snake& snake, const Maze& maze) {
  if (active) return; // Already active
  
  // Try to find a valid position
  bool validPosition = false;
  int attempts = 0;
  while (!validPosition && attempts < 50) {
    position.x = random(GRID_WIDTH);
    position.y = random(GRID_HEIGHT);
    
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
    
    attempts++;
  }
  
  if (validPosition) {
    active = true;
    lifespan = maxLifespan;
  }
}

void BonusItem::update() {
  if (active) {
    lifespan--;
    if (lifespan <= 0) {
      active = false;
    }
  }
}

void BonusItem::draw() const {
  if (!active) return;
  
  // Draw bonus item with blinking effect when about to expire
  if (lifespan > 30 || (lifespan % 8) < 4) {
    // Draw a diamond shape for bonus item
    int centerX = position.x * GRID_SIZE + GRID_SIZE / 2;
    int centerY = position.y * GRID_SIZE + GRID_SIZE / 2;
    int size = 2;
    
    arduboy.drawLine(centerX, centerY - size, centerX + size, centerY, WHITE);
    arduboy.drawLine(centerX + size, centerY, centerX, centerY + size, WHITE);
    arduboy.drawLine(centerX, centerY + size, centerX - size, centerY, WHITE);
    arduboy.drawLine(centerX - size, centerY, centerX, centerY - size, WHITE);
  }
}

bool BonusItem::isActive() const {
  return active;
}

bool BonusItem::checkCollision(const GamePoint& point) {
  if (!active) return false;
  
  if (point.x == position.x && point.y == position.y) {
    active = false;
    return true;
  }
  return false;
}

int BonusItem::getPoints() const {
  return points;
}

void BonusItem::deactivate() {
  active = false;
}