#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_set>

// Define the size of each square in the grid
constexpr float SQUARESIZE = 20.0f;
// And of the grid itself
constexpr int NUMROWS = 20;
constexpr int NUMCOLS = 10;
constexpr int OFFSET_GRID = 1;

constexpr float WINDOW_WIDTH = (NUMCOLS + 2 * OFFSET_GRID) * SQUARESIZE;
constexpr float WINDOW_HEIGHT = (NUMROWS + 2 * OFFSET_GRID) * SQUARESIZE;

// Colors
const sf::Color COLOR_BACKGROUND = sf::Color::Black;
const sf::Color COLOR_OUTLINE = sf::Color::Magenta;

// Data oriented programming

/* Data-oriented programming (DOP):
 *     - DOP is a paradigm that prioritizes data and its transformations,
 *     seeing them as the central part of any software.
 *     - In DOP, we see our software as a system that flows data from one data
 *     structure to another, making transformations along the way.
 *     - It emphasizes efficiency, with a focus on how data is stored and
 *     accessed in memory, making it particularly useful in systems where
 *     performance is critical.
 *     - DOP is more of a strategy and can be applied in any language, but it
 *     is often associated with languages like C and C++ in contexts like game
 *     development.
 */

// Structure of the program:
//  Data:
//   grid
//   blocks
//   menu
//   piece
//
//  Logic:
//   initialise
//   update piece
//   update menu
//   update blocks
//   draw

namespace Grid {
struct T {
    sf::RectangleShape grid[NUMROWS][NUMCOLS];
};

T init(sf::Vector2f origin) {
    T t = T();
    auto grid = t.grid;
    for (int row = 0; row < NUMROWS; ++row) {
        for (int col = 0; col < NUMCOLS; ++col) {
            float x = (col + origin.x) * SQUARESIZE;
            float y = (row + origin.y) * SQUARESIZE;
            grid[row][col].setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
            grid[row][col].setOutlineThickness(1.0f);
            grid[row][col].setOutlineColor(COLOR_OUTLINE);
            grid[row][col].setPosition(x, y);
        }
    }
    return t;
}

void draw(T t, sf::RenderWindow &window) {
    auto grid = t.grid;
    for (int row = 0; row < NUMROWS; ++row) {
        for (int col = 0; col < NUMCOLS; ++col) {
            window.draw(grid[row][col]);
        }
    }
}
}  // namespace Grid

namespace Blocks {
struct T {
    sf::Vector2f origin;
    std::vector<sf::RectangleShape> blocks;
};

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

}  // namespace Blocks

namespace Piece {
struct T {
    int orientation;
    int type;
    sf::Vector2f origin;
    sf::Vector2f position;
    std::vector<sf::RectangleShape> blocks;
};

sf::Color color(int type) {
    switch (type) {
        case 1:
            return sf::Color::Red;
        default:
            return sf::Color::White;
    }
}

std::vector<sf::RectangleShape> blocks(int type, sf::Vector2f origin,
                                       sf::Vector2f position) {
    std::vector<sf::RectangleShape> blocks;
    switch (type) {
        case 1: {
            float x = (origin.x + position.x) * SQUARESIZE;
            float y = (origin.y + position.y) * SQUARESIZE;

            sf::RectangleShape block1(sf::Vector2f(0, 0));
            sf::RectangleShape block2(sf::Vector2f(0, 0));
            sf::RectangleShape block3(sf::Vector2f(0, 0));
            sf::RectangleShape block4(sf::Vector2f(0, 0));

            block1.setPosition(sf::Vector2f(x + 0. * SQUARESIZE, y));
            block2.setPosition(sf::Vector2f(x + 1. * SQUARESIZE, y));
            block3.setPosition(sf::Vector2f(x + 2. * SQUARESIZE, y));
            block4.setPosition(sf::Vector2f(x + 3. * SQUARESIZE, y));

            blocks.push_back(block1);
            blocks.push_back(block2);
            blocks.push_back(block3);
            blocks.push_back(block4);

            break;
        }
        default: {
            sf::RectangleShape block(position);
            blocks.push_back(block);
            break;
        }
    }
    sf::Color blockColor = color(type);
    for (auto &block : blocks) {
        block.setFillColor(blockColor);
        block.setSize(sf::Vector2f(SQUARESIZE, SQUARESIZE));
        block.setOutlineThickness(1.0f);
        block.setOutlineColor(COLOR_OUTLINE);
    }
    return blocks;
}

T set(T t, int orientation, int type, sf::Vector2f position) {
    t.orientation = orientation;
    t.type = type;
    t.position = position;
    t.blocks = blocks(type, t.origin, position);
    return t;
}

T reset(T t) {
    int style = 1;
    return set(t, 0, style, sf::Vector2f(NUMCOLS / 2.0f, 0));
}

T copyWithOffset(const T &t, sf::Vector2f offset) {
    T copy = T(t);
    float offX = t.position.x + (offset.x);
    float offY = t.position.y + (offset.y);
    auto offsetPosition = sf::Vector2f(offX, offY);

    return set(copy, t.orientation, t.type, offsetPosition);
}

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
}  // namespace Piece

namespace State {
struct T {
    Grid::T grid;
    Blocks::T blocks;
    Piece::T piece;
};

T init() {
    auto origin = sf::Vector2f(OFFSET_GRID, OFFSET_GRID);

    Grid::T grid = Grid::init(origin);
    Blocks::T blocks = Blocks::init(origin);

    Piece::T piece = Piece::init(origin);
    piece = Piece::set(piece, 0, 1, sf::Vector2f(5, 2));

    return T(grid, blocks, piece);
}

void draw(T t, sf::RenderWindow &window) {
    Grid::draw(t.grid, window);
    Blocks::draw(t.blocks, window);
    Piece::draw(t.piece, window);
}

bool isPieceColliding(T t, Piece::T piece) {
    for (const auto &newBlock : piece.blocks) {
        if (newBlock.getPosition().x <= 0) return true;
        if (newBlock.getPosition().x > NUMCOLS * SQUARESIZE) return true;
        if (newBlock.getPosition().y > NUMROWS * SQUARESIZE) return true;

        for (const auto &existingBlock : t.blocks.blocks) {
            if (newBlock.getPosition() == existingBlock.getPosition()) {
                return true;
            }
        }
    }
    return false;
}

T move(T t, const sf::Vector2f &direction) {
    Piece::T current = t.piece;
    Piece::T newPiece = Piece::copyWithOffset(t.piece, direction);
    if (!isPieceColliding(t, newPiece)) t.piece = newPiece;
    return t;
}

T moveLeft(T t) { return move(t, sf::Vector2f(-1, 0)); }
T moveRight(T t) { return move(t, sf::Vector2f(1, 0)); }
T moveDown(T t) { return move(t, sf::Vector2f(0, 1)); }

T update(T t) {
    Piece::T current = t.piece;
    Piece::T newPiece = Piece::copyWithOffset(t.piece, sf::Vector2f(0, 1));

    if (isPieceColliding(t, newPiece)) {
        t.blocks = Blocks::addBlocks(t.blocks, current.blocks);
        t.piece = Piece::reset(current);
        // remove full lines
    } else {
        t.piece = newPiece;
    }

    return t;
}
}  // namespace State

struct TetrisPiece {
    std::vector<sf::RectangleShape> blocks;
};

constexpr float FixedNumberOfFrames = 60.0f;
constexpr float FixedTimeStep = 1.0f / FixedNumberOfFrames;
constexpr float speed = 5.0f;
constexpr float FramesBeforeFall = FixedNumberOfFrames / speed;

int main() {
    constexpr float window_width = (NUMCOLS + 2 * OFFSET_GRID) * SQUARESIZE;
    constexpr float window_height = (NUMROWS + 2 * OFFSET_GRID) * SQUARESIZE;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height),
                            "Tetris (SFML rocks!)");

    State::T state = State::init();

    sf::Clock clock;
    float deltaTime = 0.0f;
    float accumulatedTime = 0.0f;
    float accumulatedFramesBeforeFall = 0.0f;
    std::unordered_set<sf::Keyboard::Key> pressedKeys;
    auto isPressed = [&pressedKeys](sf::Keyboard::Key key) {
        return pressedKeys.count(key) > 0;
    };
    auto addPressedKey = [&pressedKeys](sf::Keyboard::Key key) {
        return pressedKeys.insert(key);
    };
    auto removePressedKey = [&pressedKeys](sf::Keyboard::Key key) {
        return pressedKeys.erase(key);
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (isPressed(event.key.code)) {
                    continue;
                }

                if (event.key.code == sf::Keyboard::Left) {
                    state = State::moveLeft(state);
                } else if (event.key.code == sf::Keyboard::Right) {
                    state = State::moveRight(state);
                } else if (event.key.code == sf::Keyboard::Down) {
                    state = State::moveDown(state);
                } else if (event.key.code == sf::Keyboard::Space) {
                }

                addPressedKey(event.key.code);
            }

            if (event.type == sf::Event::KeyReleased) {
                /* if (isPressed(event.key.code)) { */
                removePressedKey(event.key.code);
                /* } */
            }
        }

        window.clear(COLOR_BACKGROUND);

        deltaTime = clock.restart().asSeconds();
        accumulatedTime += deltaTime;

        while (accumulatedTime >= FixedTimeStep) {
            accumulatedFramesBeforeFall += 1.0f;

            // Good idea but currently does not work
            /* if (accumulatedFramesBeforeFall >= FramesBeforeFall / 2) { */
            /*     pressedKeys.clear(); */
            /* } */

            if (accumulatedFramesBeforeFall >= FramesBeforeFall) {
                state = State::update(state);
                accumulatedFramesBeforeFall = 0.0f;
            }

            accumulatedTime -= FixedTimeStep;
        }

        State::draw(state, window);

        window.display();
    }

    return 0;
}
