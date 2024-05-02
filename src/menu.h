#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

namespace Menu {

struct Multiple_choice {
  string name;
  size_t selection;
  vector<string> choices;
};

struct Single_choice {
  string name;
};

using Item = variant<Single_choice, Multiple_choice>;

struct T {
  string name;
  size_t selection;
  vector<Item> items;
  function<void(Item choice)> handle_choice;
  sf::RectangleShape background;
};

T init_main(function<void(Item choice)> handle_choice);

T selectUp(T t);
T selectDown(T t);
T selectRight(T t);
T selectLeft(T t);
void choose(T t);
void draw(T t, sf::RenderWindow &window);

} // namespace Menu

#endif // !MENU_H
