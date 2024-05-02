#include "blocks.h"
#include <SFML/Graphics.hpp>

namespace Blocks {

T init(sf::Vector2f origin) {
  T t = T{};
  t.origin = origin;
  return t;
}

void draw(T t, sf::RenderWindow &window) {
  auto blocks = t.blocks;
  for (const auto &block : blocks) {
    window.draw(block);
  }
}

T addBlocks(T t, const std::vector<sf::RectangleShape> &blocks) {
  t.blocks.insert(t.blocks.end(), blocks.begin(), blocks.end());
  return t;
}

} // namespace Blocks
