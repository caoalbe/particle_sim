cmake_minimum_required(VERSION 4.0.3)
project(particle_sim)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include directories
include_directories(
    /opt/homebrew/Cellar/sfml/3.0.1/include
    include
)

# Source files
set(SOURCES
    src/main.cpp
    src/Particle.cpp
    src/FieldLine.cpp
    src/Simulator.cpp
)

# Add executable
add_executable(main ${SOURCES})

# Link SFML libraries
target_link_directories(main PRIVATE /opt/homebrew/Cellar/sfml/3.0.1/lib)
target_link_libraries(main
    sfml-graphics
    sfml-window
    sfml-system
)