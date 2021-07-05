cmake_minimum_required(VERSION 3.16)
project(Elastic_pendulum)

set(CMAKE_CXX_STANDARD 14)

add_executable(Elastic_pendulum
        animation.cpp
        TextBar.cpp
        text.cpp
        Pendulum.cpp
        ContinuousSlider.cpp
        ButtonFrame.cpp)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Elastic_pendulum sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
