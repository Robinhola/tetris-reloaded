#include "constants.h"
#include "keys.h"
#include "menu.h"
#include "state.h"

#include "tetris_sound.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

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

  sf::Music music;
  music.openFromMemory(tetris_theme_ogg, tetris_theme_ogg_len);
  music.play();
  music.setLoop(true);

  Menu::T menu = Menu::init_main([&state, &window, &accumulatedTime,
                                  &clock](Menu::Item choice, float speed) {
    if (holds_alternative<Menu::Single_choice>(choice)) {
      auto single_choice = get<Menu::Single_choice>(choice);

      if (single_choice.name == "Restart") {
        state = State::init();
      }

      if (single_choice.name == "Play" || single_choice.name == "Restart") {
        state.name = State::Name::PLAYING;
        state.speed = speed;
        accumulatedTime = 0.f;
        clock.restart();
      } else if (single_choice.name == "Quit") {
        window.close();
      } else {
        std::cerr << "Received invalid choice: " << single_choice.name
                  << std::endl;
        throw std::invalid_argument("invalid choice");
      }

    } else {
      auto multiple_choice = get<Menu::Multiple_choice>(choice);
      if (multiple_choice.name == "Speed") {
        state.name = State::Name::PLAYING;
        state.speed = speed;
        accumulatedTime = 0.f;
        clock.restart();
      } else {
        std::cerr << "Received invalid choice: " << multiple_choice.name
                  << std::endl;
        throw std::invalid_argument("invalid choice");
      }
    }
  });

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
        if (state.name == State::Name::PLAYING) {
          if (key == sf::Keyboard::Escape) {
            state.name = State::Name::SHOWING_FIRST_MENU;
          } else {
            state = State::manageKeyPressed(state, key, true);
          }
        } else if (state.name == State::Name::SHOWING_FIRST_MENU) {
          if (key == sf::Keyboard::Escape) {
            menu.selection = 0;
            Menu::choose(menu);
          } else if (key == sf::Keyboard::Down) {

            menu = Menu::selectDown(menu);
          } else if (key == sf::Keyboard::Up) {
            menu = Menu::selectUp(menu);
          } else if (key == sf::Keyboard::Left) {
            menu = Menu::selectLeft(menu);
          } else if (key == sf::Keyboard::Right) {
            menu = Menu::selectRight(menu);
          } else if (key == sf::Keyboard::Enter) {
            Menu::choose(menu);
          }
        }
        Keys::addPressed(keys, key);
      }

      if (event.type == sf::Event::KeyReleased) {
        Keys::toBeReleased(keys, event.key.code);
      }
    }

    window.clear(COLOR_BACKGROUND);

    if (state.name == State::Name::PLAYING) {
      accumulatedTime += clock.restart().asSeconds();

      while (accumulatedTime >= fixedTimeStep) {
        state = State::manageFixedStep(state, keys);

        accumulatedTime -= fixedTimeStep;
      }
    }

    State::draw(state, window);

    if (state.name == State::Name::SHOWING_FIRST_MENU) {
      Menu::draw(menu, window);
    }

    window.display();

    Keys::removePressed(keys);
  }

  return 0;
}
