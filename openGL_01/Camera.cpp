#include "Camera.h"


/*****************************************************************************
LookAt = {	Rx	Ry	Rz	0 } * {	1	0	0	-Px }
			Ux	Uy	Uz	0		0	1	0	-Py
			Dx	Dy	Dz	0		0	0	1	-Pz
			0	0	0	1		0	0	0	1

����R����������U����������D�Ƿ�������, P�������λ��������
ע�⣬λ���������෴�ģ���Ϊ��������ϣ��������ƽ�Ƶ������������ƶ����෴����
�����LookAt������Ϊ�۲������Ժܸ�Ч�ذ�������������任���ոն���Ĺ۲�ռ䡣
LookAt��������������ֱ������������ᴴ��һ������(Look at)����Ŀ��Ĺ۲����
******************************************************************************/
Camera::Camera(glm::vec3 Position, glm::vec3 WorldUp, glm::vec3 TargetAndFront = glm::vec3(0.0f, 0.0f, -1.0f)) : pitch(PITCH), yaw(YAW), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
	cameraPos = Position;		//�ó���ԭ��������ȥ�����λ�������Ľ�������������ָ������
	cameraTarget = TargetAndFront;
	cameraFront = TargetAndFront;
	cameraDirection = glm::normalize(Position - TargetAndFront);
	worldUp = WorldUp;				//����һ��Up Vector,���������������͵ڶ����õ��ķ����������в��
	cameraRight = glm::normalize(glm::cross(worldUp, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);		//�������ͷ����������в��
		//�ڲ�˺�һЩС���ɵİ����£����Ǵ��������й��ɹ۲�/������ռ�������������Դ�������������������ķ��ʩ����������(Gram-Schmidt Process)
}

Camera::Camera(glm::vec3 Position, glm::vec3 WorldUp, float Pitch = 0.0f, float Yaw = 0.0f) : pitch(PITCH), yaw(YAW), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
	cameraPos = Position;
	worldUp = WorldUp;
	cameraFront.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)); // ��ע��direction�����������ǰ��(Front)�����ǰ���Ǻͱ��ĵ�һ��ͼƬ�ĵڶ���������ķ����������෴��
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

// ��ȡ��Ⱦʱ��
void Camera::GetMoveKeyTime() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

// �����ж�
void Camera::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	float cameraSpeed = 2.5f * deltaTime;	//������������deltaTime���ڼ����ٶȵ�ʱ����Խ��俼�ǽ�ȥ�ˣ�
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;		//�÷����ƶ�����Ϊ�ӽǷ���
		//cameraPos += cameraSpeed * glm::normalize(glm::cross(worldUp, glm::cross(cameraFront, worldUp)));		//�÷����ƶ�����ΪFPS����
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
	front.x = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw)); // ��ע��direction�����������ǰ��(Front)�����ǰ���Ǻͱ��ĵ�һ��ͼƬ�ĵڶ���������ķ����������෴��
	front.y = glm::sin(glm::radians(pitch));
	front.z = -1 * glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	cameraFront = glm::normalize(front);

}
