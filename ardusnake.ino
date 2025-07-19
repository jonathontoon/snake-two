#include <Arduboy2.h>

Arduboy2 arduboy;

const int GRID_SIZE = 8;
const int SNAKE_MAX_LENGTH = 64;

struct Point {
  int x, y;
};

Point snake[SNAKE_MAX_LENGTH];
int snakeLength = 3;
Point food;
int direction = 1; // 0=up, 1=right, 2=down, 3=left
int score = 0;
bool gameOver = false;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(8);
  initGame();
}

void loop() {
  if (!arduboy.nextFrame()) return;
  
  arduboy.clear();
  
  if (!gameOver) {
    handleInput();
    updateGame();
    drawGame();
  } else {
    drawGameOver();
    if (arduboy.justPressed(A_BUTTON)) {
      initGame();
    }
  }
  
  arduboy.display();
}

void initGame() {
  snakeLength = 3;
  direction = 1;
  score = 0;
  gameOver = false;
  
  // Initialize snake in center
  snake[0] = {WIDTH / 2 / GRID_SIZE, HEIGHT / 2 / GRID_SIZE};
  snake[1] = {snake[0].x - 1, snake[0].y};
  snake[2] = {snake[0].x - 2, snake[0].y};
  
  generateFood();
}

void handleInput() {
  if (arduboy.justPressed(UP_BUTTON) && direction != 2) direction = 0;
  if (arduboy.justPressed(RIGHT_BUTTON) && direction != 3) direction = 1;
  if (arduboy.justPressed(DOWN_BUTTON) && direction != 0) direction = 2;
  if (arduboy.justPressed(LEFT_BUTTON) && direction != 1) direction = 3;
}

void updateGame() {
  Point newHead = snake[0];
  
  switch (direction) {
    case 0: newHead.y--; break; // up
    case 1: newHead.x++; break; // right
    case 2: newHead.y++; break; // down
    case 3: newHead.x--; break; // left
  }
  
  // Check wall collision
  if (newHead.x < 0 || newHead.x >= WIDTH / GRID_SIZE || 
      newHead.y < 0 || newHead.y >= HEIGHT / GRID_SIZE) {
    gameOver = true;
    return;
  }
  
  // Check self collision
  for (int i = 0; i < snakeLength; i++) {
    if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
      gameOver = true;
      return;
    }
  }
  
  // Move snake
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;
  
  // Check food collision
  if (snake[0].x == food.x && snake[0].y == food.y) {
    score++;
    if (snakeLength < SNAKE_MAX_LENGTH) {
      snakeLength++;
    }
    generateFood();
  }
}

void generateFood() {
  bool validPosition = false;
  while (!validPosition) {
    food.x = random(WIDTH / GRID_SIZE);
    food.y = random(HEIGHT / GRID_SIZE);
    
    validPosition = true;
    for (int i = 0; i < snakeLength; i++) {
      if (snake[i].x == food.x && snake[i].y == food.y) {
        validPosition = false;
        break;
      }
    }
  }
}

void drawGame() {
  // Draw snake
  for (int i = 0; i < snakeLength; i++) {
    arduboy.fillRect(snake[i].x * GRID_SIZE, snake[i].y * GRID_SIZE, 
                     GRID_SIZE - 1, GRID_SIZE - 1, WHITE);
  }
  
  // Draw food
  arduboy.fillRect(food.x * GRID_SIZE, food.y * GRID_SIZE, 
                   GRID_SIZE - 1, GRID_SIZE - 1, WHITE);
  
  // Draw score
  arduboy.setCursor(0, 0);
  arduboy.print("Score: ");
  arduboy.print(score);
}

void drawGameOver() {
  arduboy.setCursor(32, 24);
  arduboy.print("GAME OVER");
  arduboy.setCursor(32, 32);
  arduboy.print("Score: ");
  arduboy.print(score);
  arduboy.setCursor(24, 48);
  arduboy.print("Press A to restart");
}