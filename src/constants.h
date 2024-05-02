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
constexpr float speed = 3.0f;

constexpr float FramesBeforeFall = fixedNumberOfFrames / speed;

// If you keep the key pressed, it will move the piece 2.0f times per update
constexpr float FramesBeforeMovement = FramesBeforeFall / 2.5f;

#endif // !CONSTANTS_H
