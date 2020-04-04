cmake_minimum_required(VERSION 3.15)
project(371ProceduralForest)

set(CMAKE_CXX_STANDARD 14)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(Framework)
include_directories(Structures)
include_directories(Components)
include_directories(Assets)

add_executable(ProceduralForest main.cpp Assets/Utils.h Structures/Transform.cpp Structures/Component.cpp
        Structures/Material.h Structures/Entity.cpp Structures/Shader.h)
target_link_libraries(ProceduralForest PRIVATE GLEW::GLEW PRIVATE glfw PRIVATE glm )

