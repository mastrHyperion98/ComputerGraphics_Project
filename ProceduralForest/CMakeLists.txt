cmake_minimum_required(VERSION 3.15)
project(371ProceduralForest)



set(CMAKE_CXX_STANDARD 14)
set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

find_package(GLEW REQUIRED)
find_package(glfw3  REQUIRED)
find_package(glm  REQUIRED)

include_directories(Framework)
include_directories(Structures)
include_directories(Components)
include_directories(Assets)
include_directories(Assets/Entities)
<<<<<<< Updated upstream
add_executable(ProceduralForest main.cpp Assets/Utils.h Structures/Transform.cpp Structures/Component.cpp
        Structures/Material.h Structures/Entity.cpp Structures/Shader.h Structures/Renderer.cpp
        Structures/WindowManager.cpp Structures/World.cpp Components/Cube.cpp Framework/stb_image.cpp
        Assets/Entities/Tree.cpp Assets/TreeGenerator.cpp Assets/Entities/Terrain.cpp)
target_link_libraries(ProceduralForest PRIVATE GLEW::GLEW PRIVATE glfw PRIVATE glm )
=======
add_executable(ProceduralForest main.cpp Structures/mesh.h Structures/model.h Structures/filesystem.h Structures/Transform.cpp Structures/Component.cpp
        Structures/Material.h Structures/Entity.cpp Structures/Shader.h Structures/Renderer.cpp
        Structures/WindowManager.cpp Structures/World.cpp Components/Cube.cpp Framework/stb_image.cpp
        Assets/Entities/Tree.cpp Assets/TreeGenerator.cpp Assets/TerrainGenerator.cpp Assets/Entities/TerrainV2.cpp Assets/RockGenerator.cpp Assets/RockGenerator.h Assets/Entities/Rock.cpp Assets/Entities/Rock.h)
target_link_libraries(ProceduralForest  glfw ${OpenGlLinkers} GLEW glm )
>>>>>>> Stashed changes

