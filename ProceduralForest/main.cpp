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
#include "Transform.h"
#include <WindowManager.h>
#include <Renderer.h>
#include "Entity.h"
#include "Cube.h"
#include "World.h"
#include "TreeGenerator.h"
#include "Camera.h"
using namespace glm;
using namespace std;
#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 768.0f
int main(int argc, char*argv[])
{
	   WindowManager::Initialize("Procedural Forest", SCREEN_WIDTH, SCREEN_HEIGHT);
    Renderer::Initialize(vec3(0,0.5,0.5));
    Renderer::addShader(new Shader("../Shaders/vertex_shader.glsl","../Shaders/frag_shader.glsl"));
    // Entering Main Loop
    World world;
    world.ProcedurallyGenerateWorld();


    mat4 projectionMatrix;
    mat4 viewMatrix;
    Camera cam;
	do {
		projectionMatrix = glm::perspective(cam.fov,            // field of view in degrees
			SCREEN_WIDTH / SCREEN_HEIGHT,  // aspect ratio
			0.01f, 400.0f);   // near and far (near > 0)
		viewMatrix = lookAt(cam.Position,  // eye
			cam.Position + cam.LookAt,  // center
			cam.Up); //

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

		//update camera
		cam.processMouse(dt);
		//collisions handled here
		cam.processKeyboard(dt, world.getEntities());
		

		viewMatrix = lookAt(cam.Position, cam.Position + cam.LookAt, cam.Up);
		Renderer::getCurrentShader()->setMat4("viewMatrix", viewMatrix);
	} while (!WindowManager::ExitWindow());
	// Shutdown GLFW
	Renderer::Shutdown();

	return 0;
}
