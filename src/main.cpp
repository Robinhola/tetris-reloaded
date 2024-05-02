#include "constants.h"
#include "keys.h"
#include "state.h"
#include <SFML/Graphics.hpp>

// Data oriented programming

/* Data-oriented programming (DOP):
 *     - DOP is a paradigm that prioritizes data and its transformations,
 *     seeing them as the central part of any software.
 *     - In DOP, we see our software as a system that flows data from one data
 *     structure to another, making transformations along the way.
 *     - It emphasizes efficiency, with a focus on how data is stored and
 *     accessed in memory, making it particularly useful in systems where
 *     performance is critical.
 *     - DOP is more of a strategy and can be applied in any language, but it
 *     is often associated with languages like C and C++ in contexts like game
 *     development.
 */

// Structure of the program:
//  Data:
//   grid
//   blocks
//   menu
//   piece
//
//  Logic:
//   initialise
//   update piece
//   update menu
//   update blocks
//   draw
constexpr float windowWidth = (NUMCOLS + 2 * OFFSET_GRID) * SQUARESIZE;
constexpr float windowHeight = (NUMROWS + 2 * OFFSET_GRID) * SQUARESIZE;

int main() {
  sf::VideoMode videoMode = sf::VideoMode(windowWidth, windowHeight);
  sf::RenderWindow window(videoMode, "Tetris (SFML rocks!)");
  sf::Clock clock;
  sf::Event event;

  Keys::T keys;
  State::T state = State::init();

  float accumulatedTime = 0.0f;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::KeyPressed) {
        auto key = event.key.code;
        if (Keys::isAlreadyPressed(keys, key)) {
          continue;
        }
        state = State::manageKeyPressed(state, key, true);
        Keys::addPressed(keys, key);
      }

      if (event.type == sf::Event::KeyReleased) {
        Keys::toBeReleased(keys, event.key.code);
      }
    }

    window.clear(COLOR_BACKGROUND);

    accumulatedTime += clock.restart().asSeconds();

    while (accumulatedTime >= fixedTimeStep) {
      state = State::manageFixedStep(state, keys);

      accumulatedTime -= fixedTimeStep;
    }

    State::draw(state, window);

    window.display();

    Keys::removePressed(keys);
  }

  return 0;
}
