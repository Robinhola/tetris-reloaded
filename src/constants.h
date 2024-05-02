#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

constexpr float SQUARESIZE = 80.0f;
// And of the grid itself
constexpr int NUMROWS = 20;
constexpr int NUMCOLS = 10;
constexpr int OFFSET_GRID = 1;

constexpr float WINDOW_WIDTH = (NUMCOLS + 2 * OFFSET_GRID) * SQUARESIZE;
constexpr float WINDOW_HEIGHT = (NUMROWS + 2 * OFFSET_GRID) * SQUARESIZE;

// Colors
const sf::Color COLOR_BACKGROUND = sf::Color::Black;
const sf::Color COLOR_OUTLINE = sf::Color::Magenta;

// Movement
constexpr float fixedNumberOfFrames = 60.0f;
constexpr float fixedTimeStep = 1.0f / fixedNumberOfFrames;

#endif // !CONSTANTS_H
