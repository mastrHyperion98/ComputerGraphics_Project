cmake_minimum_required(VERSION 3.15)
project(371ProceduralForest)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(ProceduralForest main.cpp)
target_link_libraries(ProceduralForest PRIVATE GLEW::GLEW PRIVATE glfw PRIVATE glm)
