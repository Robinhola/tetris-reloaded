cmake_minimum_required(VERSION 3.12)
project(Tetris-reloaded)

set(exe tetris.exe)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the path to SFML
set(SFML_DIR "/usr/include/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add your source files
add_executable(${exe}
    src/main.cpp
    src/blocks.cpp
    src/grid.cpp
    src/keys.cpp
    src/menu.cpp
    src/piece.cpp
    src/state.cpp
    # Add your other source files here
)

# Link SFML libraries to your executable
target_link_libraries(${exe}
    sfml-graphics
    sfml-audio
)
