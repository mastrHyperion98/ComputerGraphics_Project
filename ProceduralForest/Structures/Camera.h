#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <algorithm>	//for std::max to compile (windows)

class Camera
{
private:
	float ground_offset = 5.0f;
	// Other camera parameters
	float speed = 3.0f * 10/2;
	float fastSpeed = 2 * speed;
	float horizontalAngle = 90.0f;
	float verticalAngle = 0.0f;
	const float angularSpeed = 5.0f;
public:

	float collisionOffset = 0.25f; // makes camera thicker to simulate a human colliding with trees

	float fov = 70.00f;
	//this value can be increased/decreased if you walk on hills
	float ground_height = 0.0f; 
	// position camera at the origin
	glm::vec3 Position;
	glm::vec3 LookAt;
	glm::vec3 Up;


	Camera()
	{
		Position = glm::vec3(0.0f, ground_height + ground_offset, 20.0f);
		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);
		Up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void processMouse(float dt)
	{
		float theta = radians(horizontalAngle);
		float phi = radians(verticalAngle);

        verticalAngle -= WindowManager::GetMouseMotionY() * angularSpeed * dt;
        //verticalAngle += WindowManager::GetMouseMotionY() * angularSpeed * dt;      // Used to invert mouse
        horizontalAngle -= WindowManager::GetMouseMotionX() * angularSpeed * dt;

		verticalAngle = std::max(-85.0f, std::min(85.0f, verticalAngle));
		if (horizontalAngle > 360)
		{
			horizontalAngle -= 360;
		}
		else if (horizontalAngle < -360)
		{
			horizontalAngle += 360;
		}
		// forward vector -- pointing to the direction we are looking at
		LookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
	}

	bool isInsideObject(glm::vec3 center, float halfLength)
	{
		float norf = center.z - halfLength;
		float souf = center.z + halfLength;
		float east = center.x + halfLength;
		float west = center.x - halfLength;

		bool ans_x = (west <= Position.x && Position.x <= east);
		bool ans_z = (norf <= Position.z && Position.z <= souf);
		
		/*if (ans_x && ans_z)
			std::cout << "in" << std::endl;
		else
			std::cout << "out" << std::endl;*/
		
		return (ans_x && ans_z);
	}

	void processKeyboard(float dt, std::vector<Entity*> &world_entities)
	{
		glm::vec3 old_Position = Position;			//save old position in case new pos collides with objects

		vec3 cameraSideVector = glm::cross(LookAt, vec3(0.0f, 0.5f, 0.0f));
		if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
			Position -= cameraSideVector * speed * dt;
		if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
			Position += cameraSideVector * speed * dt;
		if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) // move camera up
			Position -= LookAt * speed * dt;
		if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) // move camera down
			Position += LookAt * speed * dt;

		//max height (to not fly above x units from the ground)
		Position.y = ground_height + ground_offset;	

		//handle collisions
		int i = 0;
		for (Entity* e : world_entities)
		{
			if (i++ == 0) continue;	//skip 0th element
			else
			{
				glm::vec3 position = e->getTransform()->position;
				glm::vec3 scaling = e->getTransform()->scaling;
				
				if (isInsideObject(position, collisionOffset + scaling.x/2))
				{
					Position = old_Position;
				}
			}
		}

		// we need to make the side vector a unit vector
		glm::normalize(cameraSideVector);
	}
};
