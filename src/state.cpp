#include "state.h"
#include "blocks.h"
#include "grid.h"
#include "keys.h"
#include "piece.h"
#include <sfml/graphics.hpp>

namespace State {

T init() {
  auto origin = sf::Vector2f(OFFSET_GRID, OFFSET_GRID);

  Grid::T grid = Grid::init(origin);
  Blocks::T blocks = Blocks::init(origin);

  Piece::T piece = Piece::init(origin);
  piece = Piece::set(piece, 1, 1, sf::Vector2f(5, 2));

  return T{grid, blocks, piece};
}

void draw(T t, sf::RenderWindow &window) {
  Grid::draw(t.grid, window);
  Blocks::draw(t.blocks, window);
  Piece::draw(t.piece, window);
}

bool isPieceColliding(T t, Piece::T piece) {
  for (const auto &newBlock : piece.blocks) {
    if (newBlock.getPosition().x <= 0)
      return true;
    if (newBlock.getPosition().x > NUMCOLS * SQUARESIZE)
      return true;
    if (newBlock.getPosition().y > NUMROWS * SQUARESIZE)
      return true;

    for (const auto &existingBlock : t.blocks.blocks) {
      if (newBlock.getPosition() == existingBlock.getPosition()) {
        return true;
      }
    }
  }
  return false;
}

T rotate(T t, bool positive) {
  int offset = positive ? 1 : -1;
  Piece::T newPiece = Piece::copyWithRotation(t.piece, offset);

  if (isPieceColliding(t, newPiece)) {
    return t;
  }

  t.piece = newPiece;
  return t;
}

T move(T t, const sf::Vector2f &direction) {
  t.accumulatedFramesBeforeMove = 0.0f;

  Piece::T newPiece = Piece::copyWithOffset(t.piece, direction);

  if (isPieceColliding(t, newPiece)) {
    return t;
  }

  t.piece = newPiece;
  return t;
}

T moveLeft(T t) { return move(t, sf::Vector2f(-1, 0)); }
T moveRight(T t) { return move(t, sf::Vector2f(1, 0)); }
T moveDown(T t) {
  t.accumulatedFramesBeforeFall = 0.0f;
  return move(t, sf::Vector2f(0, 1));
}

T withRemovedFullLines(T t) {
  auto &blocks = t.blocks.blocks;

  std::sort(
      blocks.begin(), blocks.end(),
      [](const sf::RectangleShape &left, const sf::RectangleShape &right) {
        return left.getPosition().y < right.getPosition().y;
      });

  // 0 indexed
  int count[NUMROWS] = {};
  for (const auto &block : blocks) {
    // 1 indexed
    int y = int(block.getPosition().y / SQUARESIZE);
    count[y - 1] += 1;
  }

  int currentOffset = 0;
  int numberOfTimesLinesShouldBeShifted[NUMROWS] = {};
  for (int i = 0; i < NUMROWS; ++i) {
    // Start from the end
    // 0 indexed
    int y = NUMROWS - i;
    if (count[y] == NUMCOLS) {
      currentOffset += 1;
    }
    numberOfTimesLinesShouldBeShifted[y] = currentOffset;
  }

  std::vector<sf::RectangleShape> shiftedBlocks;
  for (auto block : blocks) {
    // 1 indexed
    int y = int(block.getPosition().y / SQUARESIZE);
    if (count[y - 1] == NUMCOLS) {
      continue;
    }
    block.setPosition(block.getPosition().x,
                      block.getPosition().y +
                          numberOfTimesLinesShouldBeShifted[y] * SQUARESIZE);
    shiftedBlocks.push_back(block);
  }

  t.blocks.blocks = shiftedBlocks;

  return t;
}

T update(T t, bool shouldAutomaticallyFall) {
  Piece::T current = t.piece;
  Piece::T newPiece = Piece::copyWithOffset(t.piece, sf::Vector2f(0, 1));

  if (isPieceColliding(t, newPiece)) {
    t.blocks = Blocks::addBlocks(t.blocks, current.blocks);
    t.piece = Piece::reset(current);
    return withRemovedFullLines(t);
  }

  if (shouldAutomaticallyFall) {
    t.piece = newPiece;
  }

  return t;
}

T manageKeyPressed(T t, sf::Keyboard::Key key, bool wasJustPressed) {
  if (key == sf::Keyboard::Space && wasJustPressed) {
    return rotate(t, true);
  }

  if (key == sf::Keyboard::Left) {
    return moveLeft(t);
  }

  if (key == sf::Keyboard::Right) {
    return moveRight(t);
  }

  if (key == sf::Keyboard::Down) {
    return moveDown(t);
  }

  return t;
}

T manageFixedStep(T t, Keys::T keys) {
  t.accumulatedFramesBeforeMove += 1.0f;
  t.accumulatedFramesBeforeFall += 1.0f;
  t.accumulatedFramesBeforeUpdate += 1.0f;

  if (t.accumulatedFramesBeforeMove >= FramesBeforeMovement) {
    for (const auto &key : keys.pressed) {
      t = manageKeyPressed(t, key, false);
    }
  }

  if (t.accumulatedFramesBeforeUpdate >= FramesBeforeFall) {
    bool shouldAutomaticallyFall =
        t.accumulatedFramesBeforeFall >= FramesBeforeFall;

    t = State::update(t, shouldAutomaticallyFall);

    if (shouldAutomaticallyFall) {
      t.accumulatedFramesBeforeFall = 0.0f;
    }

    t.accumulatedFramesBeforeUpdate = 0.0f;
  }

  return t;
}

} // namespace State
