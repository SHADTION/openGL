#include "Shader.h"
#include "Camera.h"


#include <GLFW\glfw3.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


#define QE ==

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// Mouse Position
float lastX, lastY;
bool firstMouse = true;


// 新建一个Camera类
//Camera ourCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0));
//Camera ourCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
//Camera ourCamera(glm::vec3(0, 0, 3.0f), 30.0f, 0.0f, glm::vec3(0, 1.0f, 0));
//Camera* ourCamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, -1.0f));
Camera* ourCamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0), 0.0f, 0.0f);

void framebuffer_size_callback(GLFWwindow* Window, int Width, int Height);
void mouse_callback(GLFWwindow* Window, double XPos, double YPos);


//float vertices[] = {
//	     //---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 3, // 第一个三角形
	1, 2, 3  // 第二个三角形
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};



int main(void)
{
	// 版本号3.3；核心模式
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 开启窗口
	GLFWwindow* window_1 = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Base Window", NULL, NULL);
	if (window_1 QE NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;	
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window_1);
	
	// 初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// 初始化 
	stbi_set_flip_vertically_on_load(true);			//stb_image.h 颠倒Y轴
	glEnable(GL_DEPTH_TEST);						//启用深度测试，需开启GL_DEPTH_TEST

	// 新建一个Shader类，初始化并链接shader
	Shader ourShader("shader.vert", "shader.frag");
	
	// 确定视口
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetInputMode(window_1, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		//在调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，
																	//它也不会离开窗口。对于FPS摄像机系统来说非常完美。
	glfwSetFramebufferSizeCallback(window_1, framebuffer_size_callback);
	glfwSetCursorPosCallback(window_1, mouse_callback);				//当我们用GLFW注册了回调函数之后，鼠标一移动mouse_callback函数就会被调用

	// vertex array objeects
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// vertex buffer objects
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
/******************************************************
	 设置顶点属性指针
*******************************************************

	glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);						// 位置属性
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(11, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));	// 颜色属性，起手3个偏移量
	glEnableVertexAttribArray(11);
	glVertexAttribPointer(12, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));	// 纹理属性，起手6个偏移量
	glEnableVertexAttribArray(12);

******************************************************/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// element buffer objects
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Texture
	unsigned int texture[2];
	glGenTextures(2, texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* tex_data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (tex_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
			//第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
			//第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
			//第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
			//第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
			//下个参数应该总是被设为0（历史遗留的问题）。
			//第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
			//最后一个参数是真正的图像数据。
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture 1\n" << std::endl;
	}
	stbi_image_free(tex_data);										//释放图像的内存是一个很好的习惯
	// 第二纹理
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	tex_data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (tex_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture 2\n" << std::endl;
	}
	stbi_image_free(tex_data);										//释放图像的内存是一个很好的习惯

	
	
	

	// 通过使用glUniform1i设置每个采样器的方式告诉OpenGL每个着色器采样器属于哪个纹理单元
	ourShader.use();													//先使用shader才能改变uniform的值
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);		// 手动设置
	ourShader.setInt("texture2", 1);									// 或者使用着色器类设置

	//渲染循环
	while (!glfwWindowShouldClose(window_1))
	{

		// 输入
		ourCamera->GetMoveKeyTime();
		ourCamera->processInput(window_1);
		
		// 渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//清除颜色缓冲，通过在glClear函数中指定DEPTH_BUFFER_BIT位来清除深度缓冲
/*****************************************************************
将模型缩放位移随时间旋转
*****************************************************************
		float timeValue = (float)glfwGetTime();
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(timeValue), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5, 0.5, 0.0));						
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));							// 先缩放后位移 绕z轴旋转
		ourShader.use();										//先使用shader才能改变uniform的值
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transForm"), 1, GL_FALSE, glm::value_ptr(trans));
*******************************************************************/
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));					// 注意，我们将矩阵向我们要进行移动场景的反方向移动。
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
		view = ourCamera->GetFrontViewMatrix();
		//view = ourCamera->GetTargetViewMatrix();
		ourShader.use();										//先使用shader才能改变uniform的值
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			//我们跟踪两个全局变量来计算出deltaTime值：
			//在每一帧中我们计算出新的deltaTime以备后用。


		// 绘制物体
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			
			float angle = 20.0f * i; 
			if ((i QE 0) || ((i + 1) % 3 QE 0))
				angle = (float)glfwGetTime() * 20.0f;
			
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glBindVertexArray(VAO);									//想绘制物体先bind上对应的VAO，用于减少有多个VAO时发生错误
		//glDrawArrays(GL_TRIANGLES, 0, 36);						//不用EBO的绘制法
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//监测事件，交换缓冲
		glfwSwapBuffers(window_1);
		glfwPollEvents();
	}

	// Delete shader
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	
	// 清理资源 
	glfwTerminate();
	return 0;              
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* Window, int Width, int Height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, Width, Height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* Window, double XPos, double YPos)
{
	if (firstMouse)
	{
		lastX = (float)XPos;
		lastY = (float)YPos;
		firstMouse = false;
	}

	float XOffset = (float)XPos - lastX;
	float YOffset = -1 * ((float)YPos - lastY); // reversed since y-coordinates go from bottom to top

	lastX = (float)XPos;
	lastY = (float)YPos;

	//printf("%f   %f \n", XOffset, YOffset);

	ourCamera->mouse_callback(XOffset, YOffset);
}

//void mouse_callback(GLFWwindow* Window, double XPos, double YPos) {
//	float deltaX, deltaY;
//
//	if (firstMouse)
//	{
//		lastX = XPos;
//		lastY = YPos;
//		firstMouse = false;
//	}
//
//	deltaX = XPos - lastX;
//	deltaY = -1 * (YPos - lastY);
//	
//	lastX = XPos;
//	lastY = YPos;
//	
//	//printf("%f\n", deltaX);
//	
//	
//	float sensitivity = 0.05;
//	deltaX *= sensitivity;
//	deltaY *= sensitivity;
//	
//	yaw += deltaX;
//	pitch += deltaY;
//	
//	if (pitch > 89.0f)
//		pitch = 89.0f;
//	if (pitch < -89.0f)
//		pitch = -89.0f;
//	
//	glm::vec3 front;
//	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw)); // 译注：direction代表摄像机的前轴(Front)，这个前轴是和本文第一幅图片的第二个摄像机的方向向量是相反的
//	front.y = sin(glm::radians(pitch));
//	front.z = -1 * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//	cameraFront = glm::normalize(front);
//	
//}



/******************************************************
*******************************************************
******************************************************/

