#include "piece.h"
#include "constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Piece {

sf::Color color(int type) {
  switch (type) {
  case 1:
    return sf::Color::Red;
  case 2:
    return sf::Color::Yellow;
  case 3:
    return sf::Color::Blue;
  case 4:
    return sf::Color::Black;
  case 5:
    return sf::Color::Magenta;
  case 6:
    return sf::Color::Cyan;
  case 7:
    return sf::Color::Green;
  default:
    std::cout << "Error: no color defined for type " << type << std::endl;
    return sf::Color::Black;
  }
}

std::vector<sf::RectangleShape>
blocks(int type, int rotation, sf::Vector2f origin, sf::Vector2f position) {
  std::vector<sf::RectangleShape> blocks;

  const float x = (origin.x + position.x) * SQUARESIZE;
  const float y = (origin.y + position.y) * SQUARESIZE;

  auto translate = [x, y](float xr, float yr) {
    xr = xr * SQUARESIZE + x;
    yr = yr * SQUARESIZE + y;
    return sf::Vector2f(xr, yr);
  };

  sf::RectangleShape block0(sf::Vector2f(0, 0));
  sf::RectangleShape block1(sf::Vector2f(0, 0));
  sf::RectangleShape block2(sf::Vector2f(0, 0));
  sf::RectangleShape block3(sf::Vector2f(0, 0));

  switch (type) {
  case 1: {
    // Line: 0123
    switch (rotation) {
    case 1:
    case 3:
      block0.setPosition(translate(-2., 0.));
      block1.setPosition(translate(-1., 0.));
      block2.setPosition(translate(+0., 0.));
      block3.setPosition(translate(+1., 0.));
      break;
    case 2:
    case 4:
      block0.setPosition(translate(0., -2.));
      block1.setPosition(translate(0., -1.));
      block2.setPosition(translate(0., +0.));
      block3.setPosition(translate(0., +1.));
      break;
    }
    break;
  }
  case 2: {
    // Square: 0 1
    //         2 3
    switch (rotation) {
    case 1:
    case 2:
    case 3:
    case 4:
      block0.setPosition(translate(0., 0.));
      block1.setPosition(translate(1., 0.));
      block2.setPosition(translate(0., 1.));
      block3.setPosition(translate(1., 1.));
      break;
    }
    break;
  }
  case 3: {
    // 0 1 2
    //     3
    switch (rotation) {
    case 1:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(+1., +1.));
      break;
    case 2:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(-1., +1.));
      break;
    case 3:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(-1., -1.));
      break;
    case 4:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(+1., -1.));
      break;
    }
    break;
  }
  case 4: {
    // 0 1 2
    // 3
    switch (rotation) {
    case 1:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(-1., +1.));
      break;
    case 2:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(-1., -1.));
      break;
    case 3:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(+1., -1.));
      break;
    case 4:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(+1., +1.));
      break;
    }
    break;
  }
  case 5: {
    //   2 3
    // 0 1
    switch (rotation) {
    case 1:
    case 3:
      block0.setPosition(translate(-1., +1.));
      block1.setPosition(translate(+0., +1.));
      block2.setPosition(translate(+0., +0.));
      block3.setPosition(translate(+1., +0.));
      break;
    case 2:
    case 4:
      block0.setPosition(translate(-0., -1.));
      block1.setPosition(translate(+1., +0.));
      block2.setPosition(translate(+0., +0.));
      block3.setPosition(translate(+1., +1.));
      break;
    }
    break;
  }
  case 6: {
    // 0 1 2
    //   3
    switch (rotation) {
    case 1:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(+0., +1.));
      break;
    case 2:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(-1., +0.));
      break;
    case 3:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+1., +0.));
      block3.setPosition(translate(+0., -1.));
      break;
    case 4:
      block0.setPosition(translate(+0., -1.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(+1., +0.));
      break;
    }
    break;
  }
  case 7: {
    // 0 1
    //   2 3
    switch (rotation) {
    case 1:
    case 3:
      block0.setPosition(translate(-1., +0.));
      block1.setPosition(translate(+0., +0.));
      block2.setPosition(translate(+0., +1.));
      block3.setPosition(translate(+1., +1.));
      break;
    case 2:
    case 4:
      block0.setPosition(translate(+1., -1.));
      block1.setPosition(translate(+1., +0.));
      block2.setPosition(translate(+0., +0.));
      block3.setPosition(translate(+0., +1.));
      break;
    }
    break;
  }
  default: {
    std::cout << "Error: undefined type: " << type << std::endl;
    break;
  }
  }
  blocks.push_back(block0);
  blocks.push_back(block1);
  blocks.push_back(block2);
  blocks.push_back(block3);

  sf::Color blockOutlineColor = color(type);
  sf::Color blockColor = color(type);
  for (auto &block : blocks) {
    block.setFillColor(blockColor);
    block.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
    block.setOutlineThickness(0.5f);
    block.setOutlineColor(blockOutlineColor);
  }
  return blocks;
}

T set(T t, int orientation, int type, sf::Vector2f position) {
  t.orientation = orientation;
  t.type = type;
  t.position = position;
  t.blocks = blocks(type, orientation, t.origin, position);
  return t;
}

T reset(T t) {
  int type = t.distribution(t.gen);
  return set(t, 1, type, sf::Vector2f(NUMCOLS / 2.0f, 0));
}

T copyWithOffset(const T &t, sf::Vector2f offset) {
  T copy = T(t);
  float offX = t.position.x + (offset.x);
  float offY = t.position.y + (offset.y);
  auto offsetPosition = sf::Vector2f(offX, offY);

  return set(copy, t.orientation, t.type, offsetPosition);
}

T copyWithRotation(const T &t, int offset) {
  T copy = T(t);

  int orientation = t.orientation + 1;
  orientation = orientation > 4 ? 1 : orientation;

  return set(copy, orientation, t.type, t.position);
}

T init(sf::Vector2f origin) {
  std::random_device rd;  // Obtain a random seed from the hardware
  std::mt19937 gen(rd()); // Seed the generator
  std::uniform_int_distribution<int> distribution(1, 7); // Define the range

  T t = T{};

  t.origin = origin;
  t.gen = gen;
  t.distribution = distribution;

  return t;
}

void draw(T t, sf::RenderWindow &window) {
  auto blocks = t.blocks;
  for (const auto &block : blocks) {
    window.draw(block);
  }
}

} // namespace Piece
