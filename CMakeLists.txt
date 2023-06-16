cmake_minimum_required(VERSION 3.12)
project(Tetris-reloaded)

set(exe tetris.exe)
set(CMAKE_CXX_STANDARD 20)

# Add the path to SFML
set(SFML_DIR "/usr/include/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add your source files
add_executable(${exe}
    src/main.cpp
    # Add your other source files here
)

# Link SFML libraries to your executable
target_link_libraries(${exe}
    sfml-graphics
    sfml-audio
)
