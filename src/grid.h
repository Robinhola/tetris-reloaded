#ifndef GRID_H
#define GRID_H

#include "constants.h"

namespace Grid {
struct T {
  sf::RectangleShape grid[NUMROWS][NUMCOLS];
};

T init(sf::Vector2f origin);

void draw(T t, sf::RenderWindow &window);

} // namespace Grid

#endif // !GRID_H
