#include "Snake.h"

Snake::Snake() : length(3), dir(RIGHT) {
  body[0] = GamePoint(GRID_WIDTH / 2, GRID_HEIGHT / 2);
  body[1] = GamePoint(body[0].x - 1, body[0].y);
  body[2] = GamePoint(body[0].x - 2, body[0].y);
}

void Snake::setDirection(Direction newDir) {
  if ((dir == UP && newDir != DOWN) ||
      (dir == DOWN && newDir != UP) ||
      (dir == LEFT && newDir != RIGHT) ||
      (dir == RIGHT && newDir != LEFT)) {
    dir = newDir;
  }
}

GamePoint Snake::getHead() const {
  return body[0];
}

int Snake::getLength() const {
  return length;
}

GamePoint Snake::getBodySegment(int index) const {
  return body[index];
}

void Snake::move() {
  for (int i = length - 1; i > 0; i--) {
    body[i] = body[i - 1];
  }
  
  switch (dir) {
    case UP: body[0].y--; break;
    case RIGHT: body[0].x++; break;
    case DOWN: body[0].y++; break;
    case LEFT: body[0].x--; break;
  }
}

void Snake::applyWraparound() {
  if (body[0].x < 0) {
    body[0].x = GRID_WIDTH - 1;
  } else if (body[0].x >= GRID_WIDTH) {
    body[0].x = 0;
  }
  
  if (body[0].y < 0) {
    body[0].y = GRID_HEIGHT - 1;
  } else if (body[0].y >= GRID_HEIGHT) {
    body[0].y = 0;
  }
}

void Snake::grow() {
  if (length < 64) { // Using constant since SNAKE_MAX_LENGTH not available
    length++;
  }
}

bool Snake::checkSelfCollision() const {
  GamePoint head = body[0];
  for (int i = 1; i < length; i++) {
    if (body[i].x == head.x && body[i].y == head.y) {
      return true;
    }
  }
  return false;
}

void Snake::draw() const {
  for (int i = 0; i < length; i++) {
    arduboy.fillRect(body[i].x * GRID_SIZE, body[i].y * GRID_SIZE, 
                     GRID_SIZE - 1, GRID_SIZE - 1, WHITE);
  }
}