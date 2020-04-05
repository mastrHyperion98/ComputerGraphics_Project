
#include <iostream>
#include "GL/glew.h"   // Include GLEW - OpenGL Extension Wrangler

#include "GLFW/glfw3.h" // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs
#include "glm/gtc/matrix_transform.hpp" // include this to create transformation matrices
#include "glm/glm.hpp"  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Transform.h"
#include <WindowManager.h>
#include <Renderer.h>
#include "Entity.h"
#include "Cube.h"
#include "World.h"
int main(int argc, char*argv[])
{
    WindowManager::Initialize("Procedural Forest",1024,768);
    Renderer::Initialize(vec3(0,0.5,0.5));
    Renderer::addShader(new Shader("../Shaders/vertex_shader.glsl","../Shaders/frag_shader.glsl"));
    // Entering Main Loop
    World world;
    Material white;
    Entity entity;
    Cube *cube = new Cube(white);
    entity.addComponent(cube);
    world.AddEntities(entity);
   do{
        WindowManager::Update();
        // Update World
        float dt = WindowManager::GetFrameTime();
        Renderer::BeginFrame();
       world.Draw();
       Renderer::EndFrame();
    }while(!WindowManager::ExitWindow());
    // Shutdown GLFW
    Renderer::Shutdown();

    return 0;
}
