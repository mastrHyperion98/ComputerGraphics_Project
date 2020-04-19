#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <algorithm>	//for std::max to compile (windows)
#include "TerrainV2.h"
#include "Rock.h"
class Camera
{
private:
	float ground_offset = 5.0f;
	// Other camera parameters
	const float base_speed = 3.0f * 10 / 2;
	float speed = base_speed;
	float fastSpeed = 4 * speed;
	float jumpSpeed = 8.0f;
	float fallSpeed = 2.5 * jumpSpeed;
	float horizontalAngle = 90.0f;
	float verticalAngle = 0.0f;
	const float angularSpeed = 5.0f;
	bool initMouse = false;
	//Flight toggles
	bool shiftToggle = false;
	int lastShiftState = GLFW_RELEASE;


public:

	float collisionOffset = 0.25f * 2; // makes camera thicker to simulate a human colliding with trees

	float fov = 70.00f;
	//this value can be increased/decreased if you walk on hills
	float ground_height = 0.0f;

	// position camera at the origin
	glm::vec3 Position;
	glm::vec3 LookAt;
	glm::vec3 Up;

	glm::vec3 velocity;
	glm::vec3 jumpVelocity;
	glm::vec3 gravity;

	Camera()
	{
		Position = glm::vec3(81.0f, ground_height + ground_offset, -81.0f);
		LookAt = glm::vec3(0.0f, 0.0f, 0.0f);
		Up = glm::vec3(0.0f, 1.0f, 0.0f);

		velocity = glm::vec3(0, 0, 0);
		gravity = glm::vec3(0, -fallSpeed, 0);
	}

	void processMouse(float dt)
	{
		float theta = radians(horizontalAngle);
		float phi = radians(verticalAngle);
		// forward vector -- pointing to the direction we are looking at
		LookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));

		if (initMouse) {
			verticalAngle -= WindowManager::GetMouseMotionY() * angularSpeed * dt;
			//verticalAngle += WindowManager::GetMouseMotionY() * angularSpeed * dt;      // Used to invert mouse
			horizontalAngle -= WindowManager::GetMouseMotionX() * angularSpeed * dt;
		}

		verticalAngle = std::max(-85.0f, std::min(85.0f, verticalAngle));
		if (horizontalAngle > 360)
		{
			horizontalAngle -= 360;
		}
		else if (horizontalAngle < -360)
		{
			horizontalAngle += 360;
		}
		initMouse = true;
	}

	bool isInsideObject(glm::vec3 center, float halfLength)
	{
		float norf = center.z - halfLength;
		float souf = center.z + halfLength;
		float east = center.x + halfLength;
		float west = center.x - halfLength;

		bool ans_x = (west <= Position.x && Position.x <= east);
		bool ans_z = (norf <= Position.z && Position.z <= souf);

		return (ans_x && ans_z);
	}


	bool airborne = false;
	bool wall_collision = false;
	bool entity_collision = false;


	template <class DstType, class SrcType>
	bool IsType(const SrcType* src)
	{
		return dynamic_cast<const DstType*>(src) != nullptr;
	}

	void processKeyboard(float dt, std::vector<Entity*>& world_entities)
	{
		glm::vec3 old_Position = Position;			//save old position in case new pos collides with objects

		vec3 cameraSideVector = glm::cross(LookAt, vec3(0.0f, 0.5f, 0.0f));

		if (lastShiftState == GLFW_RELEASE && glfwGetKey(WindowManager::getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			shiftToggle = !shiftToggle;
			if (shiftToggle) {
				speed = fastSpeed;
			}
			else {
				speed = base_speed;
			}
		}
		lastShiftState = glfwGetKey(WindowManager::getWindow(), GLFW_KEY_LEFT_SHIFT);

		if (wall_collision == false)
		{
			if (shiftToggle) {
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
					Position -= cameraSideVector * speed * 2.0f * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
					Position += cameraSideVector * speed * 2.0f * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) // move camera up
					Position -= LookAt * speed * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) // move camera down
					Position += LookAt * speed * dt;
			}
			// Checks if flying
			else {
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_A) == GLFW_PRESS) // move camera to the left
					Position -= cameraSideVector * speed * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_D) == GLFW_PRESS) // move camera to the right
					Position += cameraSideVector * speed * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_S) == GLFW_PRESS) // move camera up
					Position -= LookAt * speed * dt;
				if (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_W) == GLFW_PRESS) // move camera down
					Position += LookAt * speed * dt;
			}
		}


		bool space_pressed = (glfwGetKey(WindowManager::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS);
		if (airborne == false && space_pressed == true) // jump
		{
			//std::cout << "\njumped\n";
			velocity.y = jumpSpeed;
			airborne = true;
		}

		ground_height = TerrainV2::getHeightAtPosition(Position);

		//handle collisions with walls
		int delta_height = (ground_height + ground_offset) - old_Position.y;
		if (delta_height > 0)
		{
			//walking into a wall || jumped into  wall && not high enough to climb the wall
			if (airborne == false || (airborne == true && (Position.y < ground_height + ground_offset)))
			{
				Position = old_Position;
			}
			wall_collision = true;
		}
		else
		{
			wall_collision = false;
		}

		//handle collisions with trees & rocks
		int i = 0;
		for (Entity* e : world_entities)
		{
			if (i++ == 0) continue;	//skip 0th element
			else
			{
				int radius = 1;
				if (IsType<Rock,Entity>(e))
				{
					radius = ((Rock*)e)->radius;
					
					if (isInsideObject(e->getTransform()->position, collisionOffset + radius / 2))
					{
						//- vec3{ -3.0f * cos(((Rock*)e)->angle), 0.0f, -3.0f * sin(((Rock*)e)->angle) },
						//std::cout << "[collision] rock, radius=" << radius << ",ngle=" << ((Rock*)e)->angle << std::endl;
						glm::vec3 pos = e->getTransform()->position;
						std::cout << "[collision] rock->position=(" << pos.x << "," << pos.y << "," << pos.z << ")	|| cam Position=(" << Position.x << "," << Position.y << "," << Position.z << ")" << std::endl;
						//Position = old_Position ;
						//Position = old_Position;
						entity_collision = true;
						break;
					}
					
				}
				else
				{
					
					if (isInsideObject(e->getTransform()->position, collisionOffset + radius / 2))
					{
						std::cout << "[collision] tree, radius=" << radius << std::endl;
						Position = old_Position;
						entity_collision = true;
						break;
					}
				}
				

			}
		}

		// Disable gravity if flying
		if (!shiftToggle) {
			//gravity, drag camera to ground level over time.
			Position.y = old_Position.y;            //for camera rotation to not make you fly higher or land faster while pressing directionals
			Position = Position + velocity * dt;
			velocity = velocity + gravity * dt;
		}

		//correct height if it's below the ground level & set velocity to 0
		if (Position.y <= ground_height + ground_offset)	//camera is at ground level here
		{
			if (wall_collision == false || Position.y < -10)	//||Position.y<-10 in case it's falling through the floor (initial spawn)
			{
				velocity.y = 0.0f;
				Position.y = ground_height + ground_offset;
			}

			//if (airborne == true)
			//	std::cout << "\nlanded.\n";
			airborne = false;
		}
		else //camera is airborne here
		{
			//if (airborne == false)
				//std::cout << "\nairborne...\n";
			airborne = true;
			//std::cout << "y=" << Position.y << std::endl;
		}

		// we need to make the side vector a unit vector
		glm::normalize(cameraSideVector);
	}
};
