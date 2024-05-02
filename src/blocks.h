#ifndef BLOCKS_CPP
#define BLOCKS_CPP

#include <SFML/Graphics.hpp>

namespace Blocks {
struct T {
  sf::Vector2f origin;
  std::vector<sf::RectangleShape> blocks;
};

T init(sf::Vector2f origin);

void draw(T t, sf::RenderWindow &window);

T addBlocks(T t, const std::vector<sf::RectangleShape> &blocks);

} // namespace Blocks

#endif
