#include "keys.h"
#include <sfml/graphics.hpp>
#include <unordered_set>

namespace Keys {

bool isAlreadyPressed(const T &t, sf::Keyboard::Key key) {
  return t.pressed.count(key) > 0;
}

void addPressed(T &t, sf::Keyboard::Key key) { t.pressed.emplace(key); }

void toBeReleased(T &t, sf::Keyboard::Key key) {
  t.toBeReleased.push_back(key);
}

void removePressed(T &t) {
  for (const auto &key : t.toBeReleased) {
    t.pressed.erase(key);
  }
  t.toBeReleased.clear();
}

} // namespace Keys
