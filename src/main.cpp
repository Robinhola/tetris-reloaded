#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
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
    std::mt19937 gen;                                 // Seed the generator
    std::uniform_int_distribution<int> distribution;  // Define the range
};

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
            std::cout << "Error: no color defined for type " << type
                      << std::endl;
            return sf::Color::Black;
    }
}

std::vector<sf::RectangleShape> blocks(int type, int rotation,
                                       sf::Vector2f origin,
                                       sf::Vector2f position) {
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
    std::random_device rd;   // Obtain a random seed from the hardware
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_int_distribution<int> distribution(1, 7);  // Define the range

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

T rotate(T t, bool positive) {
    int offset = positive ? 1 : -1;
    Piece::T current = t.piece;
    Piece::T newPiece = Piece::copyWithRotation(t.piece, offset);
    if (!isPieceColliding(t, newPiece)) t.piece = newPiece;
    return t;
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

T removeFulllines(T t) {
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
        block.setPosition(
            block.getPosition().x,
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
        t = removeFulllines(t);
    } else {
        if (shouldAutomaticallyFall) {
            t.piece = newPiece;
        }
    }

    return t;
}

T movePiece(T t, sf::Keyboard::Key key, float *accumulatedFramesBeforeMove,
            float *accumulatedFramesBeforeFall) {
    if (key == sf::Keyboard::Left) {
        t = State::moveLeft(t);
        *accumulatedFramesBeforeMove = 0.0f;
    } else if (key == sf::Keyboard::Right) {
        t = State::moveRight(t);
        *accumulatedFramesBeforeMove = 0.0f;
    } else if (key == sf::Keyboard::Down) {
        t = State::moveDown(t);
        *accumulatedFramesBeforeMove = 0.0f;
        *accumulatedFramesBeforeFall = 0.0f;
    }

    return t;
}
}  // namespace State

namespace Keys {
struct T {
    std::unordered_set<sf::Keyboard::Key> pressed;
    std::vector<sf::Keyboard::Key> toBeReleased;
};

bool isPressed(const T &t, sf::Keyboard::Key key) {
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

}  // namespace Keys

constexpr float FixedNumberOfFrames = 60.0f;
constexpr float FixedTimeStep = 1.0f / FixedNumberOfFrames;
constexpr float speed = 3.0f;
constexpr float FramesBeforeFall = FixedNumberOfFrames / speed;

// If you keep the key pressed, it will move the piece 2.0f times per update
constexpr float FramesBeforeMovement = FramesBeforeFall / 2.5f;

int main() {
    constexpr float window_width = (NUMCOLS + 2 * OFFSET_GRID) * SQUARESIZE;
    constexpr float window_height = (NUMROWS + 2 * OFFSET_GRID) * SQUARESIZE;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height),
                            "Tetris (SFML rocks!)");

    sf::Clock clock;

    float accumulatedTime = 0.0f;
    float accumulatedFramesBeforeFall = 0.0f;
    float accumulatedFramesBeforeMove = 0.0f;
    float accumulatedFramesBeforeRotation = 0.0f;
    float accumulatedFramesBeforeUpdate = 0.0f;

    Keys::T keys;

    State::T state = State::init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                auto key = event.key.code;

                if (Keys::isPressed(keys, key)) continue;

                auto moveAcc = &accumulatedFramesBeforeMove;
                auto fallAcc = &accumulatedFramesBeforeFall;

                if (key == sf::Keyboard::Space) {
                    state = State::rotate(state, true);
                    // We could something fun here
                    /* accumulatedFramesBeforeFall = */
                } else {
                    state = State::movePiece(state, key, moveAcc, fallAcc);
                }

                Keys::addPressed(keys, key);
            }

            if (event.type == sf::Event::KeyReleased) {
                Keys::toBeReleased(keys, event.key.code);
            }
        }

        window.clear(COLOR_BACKGROUND);

        accumulatedTime += clock.restart().asSeconds();
        while (accumulatedTime >= FixedTimeStep) {
            accumulatedFramesBeforeMove += 1.0f;
            accumulatedFramesBeforeFall += 1.0f;
            accumulatedFramesBeforeUpdate += 1.0f;

            if (accumulatedFramesBeforeMove >= FramesBeforeMovement) {
                for (const auto &key : keys.pressed) {
                    state = State::movePiece(state, key,
                                             &accumulatedFramesBeforeMove,
                                             &accumulatedFramesBeforeFall);
                }
            }

            if (accumulatedFramesBeforeUpdate >= FramesBeforeFall) {
                bool shouldAutomaticallyFall =
                    accumulatedFramesBeforeFall >= FramesBeforeFall;
                state = State::update(state, shouldAutomaticallyFall);
                if (shouldAutomaticallyFall) {
                    accumulatedFramesBeforeFall = 0.0f;
                }
                accumulatedFramesBeforeUpdate = 0.0f;
            }

            accumulatedTime -= FixedTimeStep;
        }

        State::draw(state, window);

        window.display();

        Keys::removePressed(keys);
    }

    return 0;
}
