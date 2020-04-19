/*
 * Created by Steven SMith
 // Created for Concordia W 2020 Comp 371
* Main driver for the Procedural Forest project
 */
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
<<<<<<< Updated upstream
using namespace glm;
using namespace std;
=======
#include "Camera.h"
#include "filesystem.h"


using namespace glm;
using namespace std;
#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 768.0f

unsigned int loadTexture(const char *path);
unsigned int loadCubemap(vector<std::string> faces);

>>>>>>> Stashed changes
int main(int argc, char*argv[])
{
    WindowManager::Initialize("Procedural Forest",1024,768);
    Renderer::Initialize(vec3(0,0.5,0.5));
    Renderer::addShader(new Shader("../Shaders/vertex_shader.glsl","../Shaders/frag_shader.glsl"));

    // build and compile shaders
    // -------------------------
    Renderer::addShader(new Shader("../Shaders/cubemaps.vs", "../Shaders/cubemaps.fs"));
    Renderer::addShader(new Shader("../Shaders/skyboxShader.vs", "../Shaders/skyboxShader.fs"));

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float cubeVertices[] = {
            // positions          // normals
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    float skyboxVertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    // cube VAO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // load textures
    // -------------
    vector<std::string> faces
            {
                    FileSystem::getPath("Assets/Textures/skybox/right.jpg"),
                    FileSystem::getPath("Assets/Textures/skybox/left.jpg"),
                    FileSystem::getPath("Assets/Textures/skybox/top.jpg"),
                    FileSystem::getPath("Assets/Textures/skybox/bottom.jpg"),
                    FileSystem::getPath("Assets/Textures/skybox/front.jpg"),
                    FileSystem::getPath("Assets/Textures/skybox/back.jpg"),
            };
    unsigned int cubemapTexture = loadCubemap(faces);



    // Entering Main Loop
    World world;
    world.ProcedurallyGenerateWorld();

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

<<<<<<< Updated upstream
       // we need to make the side vector a unit vector
       glm::normalize(cameraSideVector);
       viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp );
       Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
    }while(!WindowManager::ExitWindow());
    // Shutdown GLFW
    Renderer::Shutdown();
=======
		viewMatrix = lookAt(cam.Position, cam.Position + cam.LookAt, cam.Up);
		Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);

        // draw scene as normal
       // Renderer::getCurrentShader()->setMat4("projectionMatrix", projectionMatrix);
     //   Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
        // cubes
        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
       // Renderer::getCurrentShader()->setMat4("projectionMatrix", projectionMatrix);
       // Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

	} while (!WindowManager::ExitWindow());
	// Shutdown GLFW
	Renderer::Shutdown();
>>>>>>> Stashed changes

    return 0;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
