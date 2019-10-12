#include "Camera.h"


/*****************************************************************************
LookAt = {	Rx	Ry	Rz	0 } * {	1	0	0	-Px }
			Ux	Uy	Uz	0		0	1	0	-Py
			Dx	Dy	Dz	0		0	0	1	-Pz
			0	0	0	1		0	0	0	1

其中R是右向量，U是上向量，D是方向向量, P是摄像机位置向量。
注意，位置向量是相反的，因为我们最终希望把世界平移到与我们自身移动的相反方向。
把这个LookAt矩阵作为观察矩阵可以很高效地把所有世界坐标变换到刚刚定义的观察空间。
LookAt矩阵就像它的名字表达的那样：它会创建一个看着(Look at)给定目标的观察矩阵
******************************************************************************/
Camera::Camera(glm::vec3 Position, glm::vec3 WorldUp, glm::vec3 TargetAndFront = glm::vec3(0.0f, 0.0f, -1.0f)) : pitch(PITCH), yaw(YAW), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
	cameraPos = Position;		//用场景原点向量减去摄像机位置向量的结果就是摄像机的指向向量
	cameraTarget = TargetAndFront;
	cameraFront = TargetAndFront;
	cameraDirection = glm::normalize(Position - TargetAndFront);
	worldUp = WorldUp;				//定义一个Up Vector,接下来把上向量和第二步得到的方向向量进行叉乘
	cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);		//右向量和方向向量进行叉乘
		//在叉乘和一些小技巧的帮助下，我们创建了所有构成观察/摄像机空间的向量。在线性代数中这个处理叫做格拉姆—施密特正交化(Gram-Schmidt Process)
}

Camera::Camera(glm::vec3 Position, glm::vec3 WorldUp, float Pitch = 0.0f, float Yaw = 0.0f) : pitch(PITCH), yaw(YAW), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
	cameraPos = Position;
	worldUp = WorldUp;
	cameraFront.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)); // 译注：direction代表摄像机的前轴(Front)，这个前轴是和本文第一幅图片的第二个摄像机的方向向量是相反的
	cameraFront.y = sin(glm::radians(Pitch));
	cameraFront.z = -1 * cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
}

Camera::~Camera() {

}

glm::mat4 Camera::GetTargetViewMatrix() {
	return glm::lookAt(cameraPos, cameraTarget, worldUp);
}

glm::mat4 Camera::GetFrontViewMatrix() {
	return glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
}

// 获取渲染时间
void Camera::GetMoveKeyTime() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

// 按键判断
void Camera::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = 2.5f * deltaTime;	//现在我们有了deltaTime，在计算速度的时候可以将其考虑进去了：
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;		//该方法移动方向为视角方向
		//cameraPos += cameraSpeed * glm::normalize(glm::cross(worldUp, glm::cross(cameraFront, worldUp)));		//该方法移动方向为FPS方向
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
		//cameraPos -= cameraSpeed * glm::normalize(glm::cross(worldUp, glm::cross(cameraFront, worldUp)));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, worldUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos += worldUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		cameraPos -= worldUp * cameraSpeed;
}

void Camera::mouse_callback(float XPos, float YPos) {
	XPos *= mouseSensitivity;
	YPos *= mouseSensitivity;

	yaw += XPos;
	pitch += YPos;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw)); // 译注：direction代表摄像机的前轴(Front)，这个前轴是和本文第一幅图片的第二个摄像机的方向向量是相反的
	front.y = glm::sin(glm::radians(pitch));
	front.z = -1 * glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	cameraFront = glm::normalize(front);

}
