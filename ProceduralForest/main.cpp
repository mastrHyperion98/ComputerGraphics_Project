
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
#include "TreeGenerator.h"
using namespace glm;
using namespace std;
int main(int argc, char*argv[])
{
    WindowManager::Initialize("Procedural Forest",1024,768);
    Renderer::Initialize(vec3(0,0.5,0.5));
    Renderer::addShader(new Shader("../Shaders/vertex_shader.glsl","../Shaders/frag_shader.glsl"));
    // Entering Main Loop
    World world;
   // world.AddEntities(TreeGenerator::generateTree(vec3{0,0,0}));
    world.AddEntities(TreeGenerator::generateTree(vec3{0.0,0,-20}));

    float fov = 70.00f;
    // position camera at the origin
    vec3 cameraPosition(0.0f,5.0f,20.0f);
    vec3 cameraLookAt(0.0f, 0.0f, 0.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);
    // Other camera parameters
    float cameraSpeed = 3.0f;
    float cameraFastSpeed = 2 * cameraSpeed;
    float cameraHorizontalAngle = 90.0f;
    float cameraVerticalAngle =  0.0f;

    mat4 projectionMatrix;
    mat4 viewMatrix;
   do{
       projectionMatrix = glm::perspective(fov,            // field of view in degrees
                                                1024.0f / 768.0f,  // aspect ratio
                                                0.01f, 100.0f);   // near and far (near > 0)
       viewMatrix = lookAt(cameraPosition,  // eye
                                cameraPosition + cameraLookAt,  // center
                                cameraUp ); //

        WindowManager::Update();
        // Update World
        float dt = WindowManager::GetFrameTime();
        Renderer::BeginFrame();
        // set uniforms
        Renderer::getCurrentShader()->setMat4("projectionMatrix", projectionMatrix);
        Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
        Renderer::setRenderMode(GL_TRIANGLES);
        world.Draw();
       Renderer::EndFrame();
       // update camera
       const float cameraAngularSpeed = 60.0f;
       if(glfwGetMouseButton(WindowManager::getWindow(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS){
           cameraVerticalAngle   -= WindowManager::GetMouseMotionY() * cameraAngularSpeed * dt;

       }
       if(glfwGetMouseButton(WindowManager::getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
           cameraHorizontalAngle -= WindowManager::GetMouseMotionX()* cameraAngularSpeed * dt;
       }
       cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, cameraVerticalAngle));
       if (cameraHorizontalAngle > 360)
       {
           cameraHorizontalAngle -= 360;
       }
       else if (cameraHorizontalAngle < -360)
       {
           cameraHorizontalAngle += 360;
       }
       float theta = radians(cameraHorizontalAngle);
       float phi = radians(cameraVerticalAngle);
       vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 0.5f, 0.0f));
       if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
       {
           cameraPosition -= cameraSideVector * cameraSpeed * dt;
       }

       if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
       {
          cameraPosition += cameraSideVector * cameraSpeed * dt;
       }

       if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) // move camera up
       {
           cameraPosition -= cameraLookAt * cameraSpeed * dt;
       }

       if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) // move camera down
       {
           cameraPosition += cameraLookAt * cameraSpeed * dt;
       }
       // forward vector -- pointing to the direction we are looking at
       cameraLookAt = vec3(cosf(phi)*cosf(theta), sinf(phi), -cosf(phi)*sinf(theta));
       // side vector

       // we need to make the side vector a unit vector
       glm::normalize(cameraSideVector);
       viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp );
       Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
    }while(!WindowManager::ExitWindow());
    // Shutdown GLFW
    Renderer::Shutdown();

    return 0;
}
