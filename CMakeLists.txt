cmake_minimum_required(VERSION 3.16)
project(E)

set(CMAKE_CXX_STANDARD 14)

add_executable(E
        animation.cpp
        TextBar.cpp
        text.cpp
        Button.cpp
        Pendulum.cpp)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(E sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
