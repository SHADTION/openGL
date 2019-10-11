#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>

#define QE ==

// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
	Camera(glm::vec3 Position, glm::vec3 WorldUp, glm::vec3 TargetAndFront);
	Camera(glm::vec3 Position, glm::vec3 WorldUp, float Pitch, float Yaw);
	~Camera();

	glm::vec3 cameraPos;
	glm::vec3 cameraDirection;
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 worldUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	// Mouse Position
	float yaw, pitch;
	bool firstMouse = true;
    // Camera options
    float movementSpeed;
    float mouseSensitivity;

	glm::mat4 GetTargetViewMatrix();
	glm::mat4 GetFrontViewMatrix();
	void GetMoveKeyTime();
	void processInput(GLFWwindow* window);
	void mouse_callback(float XPos, float YPos);
};

