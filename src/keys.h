#ifndef KEYS_H
#define KEYS_H

#include <sfml/graphics.hpp>
#include <unordered_set>

namespace Keys {
struct T {
  std::unordered_set<sf::Keyboard::Key> pressed;
  std::vector<sf::Keyboard::Key> toBeReleased;
};

bool isAlreadyPressed(const T &t, sf::Keyboard::Key key);

void addPressed(T &t, sf::Keyboard::Key key);

void toBeReleased(T &t, sf::Keyboard::Key key);

void removePressed(T &t);

} // namespace Keys

#endif // !KEYS_H
