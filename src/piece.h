#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <random>

namespace Piece {
struct T {
  int orientation;
  int type;
  sf::Vector2f origin;
  sf::Vector2f position;
  std::vector<sf::RectangleShape> blocks;
  std::mt19937 gen;                                // Seed the generator
  std::uniform_int_distribution<int> distribution; // Define the range
};

sf::Color color(int type);

std::vector<sf::RectangleShape>
blocks(int type, int rotation, sf::Vector2f origin, sf::Vector2f position);
T set(T t, int orientation, int type, sf::Vector2f position);
T reset(T t);
T copyWithOffset(const T &t, sf::Vector2f offset);
T copyWithRotation(const T &t, int offset);
T init(sf::Vector2f origin);
void draw(T t, sf::RenderWindow &window);

} // namespace Piece

#endif // !PIECE_H
