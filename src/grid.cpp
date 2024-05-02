#include "grid.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

namespace Grid {

T init(sf::Vector2f origin) {
  T t = T();
  auto grid = t.grid;
  for (int row = 0; row < NUMROWS; ++row) {
    for (int col = 0; col < NUMCOLS; ++col) {
      float x = (col + origin.x) * SQUARESIZE;
      float y = (row + origin.y) * SQUARESIZE;
      grid[row][col].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
      grid[row][col].setOutlineThickness(1.0f);
      grid[row][col].setOutlineColor(COLOR_OUTLINE);
      grid[row][col].setPosition(x, y);
    }
  }
  return t;
}

void draw(T t, sf::RenderWindow &window) {
  auto grid = t.grid;
  for (int row = 0; row < NUMROWS; ++row) {
    for (int col = 0; col < NUMCOLS; ++col) {
      window.draw(grid[row][col]);
    }
  }
}
} // namespace Grid
