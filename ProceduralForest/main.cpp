
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
int main(int argc, char*argv[])
{
    WindowManager::Initialize("Procedural Forest",1024,768);
    Renderer::Initialize(vec3(1,1,1));
    // Entering Main Loop
   do{
        WindowManager::Update();
        // Update World
        float dt = WindowManager::GetFrameTime();
        Renderer::BeginFrame();
        Renderer::EndFrame();
    }while(!WindowManager::ExitWindow());
    // Shutdown GLFW
    WindowManager::Shutdown();
    Renderer::Shutdown();

    return 0;
}
