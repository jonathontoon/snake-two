#include <Arduboy2.h>
#include "Game.h"

Arduboy2 arduboy;
Game game;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(8);
  game.reset();
}

void loop() {
  if (!arduboy.nextFrame()) return;
  
  arduboy.clear();
  
  if (!game.isGameOver()) {
    game.handleInput();
    game.update();
    game.draw();
  } else {
    game.draw();
    if (arduboy.justPressed(A_BUTTON)) {
      game.reset();
    }
  }
  
  arduboy.display();
}

