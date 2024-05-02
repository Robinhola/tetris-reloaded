#ifndef STATE_H
#define STATE_H

#include "blocks.h"
#include "grid.h"
#include "keys.h"
#include "piece.h"
#include <SFML/Graphics.hpp>

namespace State {

enum Name {
  SHOWING_FIRST_MENU,
  PLAYING,
  LOST,
  WON,
};

struct T {
  // show menu, select with keys and validate with enter
  // make selected item blink with fixed step
  // - Start
  // - Difficulty

  // Menu:
  // - Resume
  // - Restart
  // - Change difficulty

  // Lose progress warning

  // Show score
  // Show next piece

  Grid::T grid;
  Blocks::T blocks;
  Piece::T piece;

  float accumulatedFramesBeforeFall = 0.0f;
  float accumulatedFramesBeforeMove = 0.0f;
  float accumulatedFramesBeforeUpdate = 0.0f;

  Name name = SHOWING_FIRST_MENU;
  float speed = 1.0f;
};

T init();

void draw(T t, sf::RenderWindow &window);

T rotate(T t, bool positive);

T update(T t, bool shouldAutomaticallyFall);

T manageKeyPressed(T t, sf::Keyboard::Key key, bool wasJustPressed);
T manageFixedStep(T t, Keys::T keys);

} // namespace State

#endif // !STATE_H
