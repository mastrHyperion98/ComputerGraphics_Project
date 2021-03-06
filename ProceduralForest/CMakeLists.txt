cmake_minimum_required(VERSION 3.15)
project(371ProceduralForest)

set(CMAKE_CXX_STANDARD 14)

# If you are using Linux, please uncomment this line

#set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

#Execute Windows only command
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

include_directories(Framework)
include_directories(Structures)
include_directories(Components)
include_directories(Assets)
include_directories(Assets/Entities)
add_executable(ProceduralForest main.cpp Structures/Transform.cpp Structures/Component.cpp
        Structures/Material.h Structures/Entity.cpp Structures/Shader.h Structures/Renderer.cpp
        Structures/WindowManager.cpp Structures/World.cpp Components/Cube.cpp Framework/stb_image.cpp
        Assets/Entities/Tree.cpp Assets/TreeGenerator.cpp Assets/TerrainGenerator.cpp Assets/Entities/TerrainV2.cpp Assets/RockGenerator.cpp Assets/RockGenerator.h Assets/Entities/Rock.cpp Assets/Entities/Rock.h)

if(WIN32)
    target_link_libraries(ProceduralForest PRIVATE GLEW::GLEW PRIVATE glfw PRIVATE glm )

endif(WIN32)
if(UNIX)
    #Execute Unix only command
    set(OpenGlLinkers -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.
    target_link_libraries(ProceduralForest PRIVATE GLEW::GLEW PRIVATE glfw PRIVATE glm  ${OpenGlLinkers})
endif(UNIX)



