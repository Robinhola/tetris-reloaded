#include "menu.h"
#include "constants.h"
#include "font.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <variant>
#include <vector>

using namespace std;

namespace Menu {

T init_main(function<void(Item choice, float speed)> handle_choice) {

  sf::RectangleShape background;
  background.setFillColor(sf::Color(252, 118, 109, 128));
  background.setSize(sf::Vector2(WINDOW_WIDTH * .8f, WINDOW_HEIGHT * .8f));
  background.setPosition(sf::Vector2(WINDOW_WIDTH * .1f, WINDOW_HEIGHT * .1f));

  return T{"Menu",
           0,
           {
               Menu::Single_choice{"Play"},
               Menu::Single_choice{"Restart"},
               Menu::Multiple_choice{"Speed", 0, {"1", "2", "3"}},
               Menu::Single_choice{"Quit"},
           },
           handle_choice,
           background};
}

float getSpeed(T t) {
  auto speed_choice = get<Multiple_choice>(t.items[2]);
  auto selection = speed_choice.choices[speed_choice.selection];
  if (selection == "1") {
    return 2.f;
  } else if (selection == "2") {
    return 4.f;
  } else if (selection == "3") {
    return 6.f;
  }
  throw std::invalid_argument("invalid speed");
}

T selectVertical(T t, size_t offset) {
  t.selection += t.items.size() + offset;
  t.selection %= t.items.size();
  return t;
}

T selectHorizontal(T t, size_t offset) {
  auto selected = t.items[t.selection];

  if (holds_alternative<Single_choice>(selected)) {
    return t;
  }

  auto multiple_choice = get<Multiple_choice>(selected);
  multiple_choice.selection += offset;
  multiple_choice.selection += multiple_choice.choices.size();
  multiple_choice.selection %= multiple_choice.choices.size();
  t.items[t.selection] = multiple_choice;

  return t;
}

T selectUp(T t) { return selectVertical(t, -1); }
T selectDown(T t) { return selectVertical(t, +1); }

T selectRight(T t) { return selectHorizontal(t, +1); }
T selectLeft(T t) { return selectHorizontal(t, -1); }

void choose(T t) { t.handle_choice(t.items[t.selection], getSpeed(t)); }

void setStyle(sf::Text &name, bool isSelected) {
  if (isSelected) {
    name.setFillColor(sf::Color::White);
    name.setStyle(sf::Text::Bold | sf::Text::Underlined);
  } else {
    name.setFillColor(sf::Color::Magenta);
    name.setStyle(sf::Text::Regular);
  }
}

void draw(T t, sf::RenderWindow &window) {
  window.draw(t.background);

  sf::Text name;
  sf::Font font;

  font.loadFromMemory(ARCADECLASSIC_TTF, ARCADECLASSIC_TTF_len);

  int pixels = WINDOW_HEIGHT / 12.f;
  int pwidth = WINDOW_WIDTH / 12.f;
  int lineHeight = pixels * 1.2f;

  name.setFont(font); // font is a sf::Font
  name.setString(t.name);
  name.setCharacterSize(pixels); // in pixels, not points!
  name.setFillColor(sf::Color::Magenta);
  name.setPosition(t.background.getPosition());

  window.draw(name);

  for (int i = 0; i < t.items.size(); i++) {
    auto item = t.items[i];
    float offset = (i + 1) * lineHeight;

    if (holds_alternative<Single_choice>(item)) {
      auto choice = get<Single_choice>(item);
      name.setString(choice.name);
      setStyle(name, i == t.selection);
      name.setPosition(t.background.getPosition() + sf::Vector2f(0.f, offset));
      window.draw(name);
    } else {
      auto choice = get<Multiple_choice>(item);
      name.setString(choice.name);
      setStyle(name, i == t.selection);
      name.setPosition(t.background.getPosition() + sf::Vector2f(0.f, offset));
      window.draw(name);

      sf::Vector2f option_offset =
          sf::Vector2f((t.name.size() + 1) * pwidth, offset);

      for (int j = 0; j < choice.choices.size(); ++j) {
        string choiceValue = choice.choices[j];
        name.setString(choiceValue);
        setStyle(name, j == choice.selection);
        name.setPosition(t.background.getPosition() + option_offset);
        window.draw(name);
        option_offset += sf::Vector2f((choiceValue.size() + 1) * pwidth, 0.f);
      }
    }
  }

  // display background
  // display name
  // display each item line by line
}

} // namespace Menu
