﻿#include "Shader.h"
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

#pragma region Model Data
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
											  
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
											  
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-2.8f, -3.0f, -4.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion


#pragma region Camera Declare
// 新建一个Camera类
//Camera ourCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0));
//Camera ourCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
//Camera ourCamera(glm::vec3(0, 0, 3.0f), 30.0f, 0.0f, glm::vec3(0, 1.0f, 0));
//Camera* ourCamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0), glm::vec3(0, 0, -1.0f));
Camera* ourCamera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 1.0f, 0), 0.0f, 0.0f);
#pragma endregion


#pragma region Input Declare
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


unsigned int loadImageToGUP(const char* ImageName, GLint InternalFormat, GLenum Format) {
	// Texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 加载并生成纹理
	int width, height, nrChannels;
	unsigned char* tex_data = stbi_load(ImageName, &width, &height, &nrChannels, 0);
	if (tex_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, GL_UNSIGNED_BYTE, tex_data);
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
		std::cout << "Failed to load texture "<< ImageName <<" \n" << std::endl;
	}
	stbi_image_free(tex_data);										//释放图像的内存是一个很好的习惯
	return texture;
}
#pragma endregion

int main(void)
{
	#pragma region Open Window
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

	
		// 确定视口
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

		glfwSetInputMode(window_1, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		//在调用这个函数之后，无论我们怎么去移动鼠标，光标都不会显示了，
																		//它也不会离开窗口。对于FPS摄像机系统来说非常完美。
		glfwSetFramebufferSizeCallback(window_1, framebuffer_size_callback);
		glfwSetCursorPosCallback(window_1, mouse_callback);				//当我们用GLFW注册了回调函数之后，鼠标一移动mouse_callback函数就会被调用
	#pragma endregion


	#pragma region Init Shader Program
		// 新建一个Shader类，初始化并链接shader
			Shader objectShader("Object.vert", "Object.frag");
			Shader colorShader("Colors.vert", "Colors.frag");
			Shader lightShader("Lights.vert", "Lights.frag");
	#pragma endregion


	#pragma region Init and Load Models to VAO & VBO
		// vertex buffer objects
		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		// vertex array objeects
		unsigned int awesomeVAO;
		glGenVertexArrays(1, &awesomeVAO);
		glBindVertexArray(awesomeVAO);

		// 设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// light vertex array objeects
		unsigned int lightVAO;
		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	#pragma endregion
	

	#pragma region Init and Load Texture
		unsigned int texture[2];

		texture[0] = loadImageToGUP("container.jpg", GL_RGB, GL_RGB);
		texture[1] = loadImageToGUP("awesomeface.png", GL_RGBA, GL_RGBA);
		
		//// 通过使用glUniform1i设置每个采样器的方式告诉OpenGL每个着色器采样器属于哪个纹理单元
		//objectShader.use();													//先使用shader才能改变uniform的值
		//glUniform1i(glGetUniformLocation(objectShader.ID, "texture0"), 0);		// 手动设置
		//objectShader.setInt("texture1", 1);									// 或者使用着色器类设置
	#pragma endregion


	#pragma region Prepare MVP matrices
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
	#pragma endregion


	//渲染循环
	while (!glfwWindowShouldClose(window_1))
	{

		// Process Input
		ourCamera->GetMoveKeyTime();
		ourCamera->processInput(window_1);
		
		// Clear Screen
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//清除颜色缓冲，通过在glClear函数中指定DEPTH_BUFFER_BIT位来清除深度缓冲

		#pragma region texture object
				// Set Model matrix
				model = glm::mat4(1.0f);
				float angle = (float)glfwGetTime() * 20.0f;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

				// Set View and Projection Matrices here if you want.
				view = ourCamera->GetFrontViewMatrix();
		
		
				// Set Material -> Shader Program
				objectShader.use();										//先使用shader才能改变uniform的值
				// Set Material -> Textures
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture[0]);
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, texture[1]);
				// Set Material -> Uniforms
				glUniform1i(glGetUniformLocation(objectShader.ID, "texture0"), 0);
				glUniform1i(glGetUniformLocation(objectShader.ID, "texture2"), 2);
				glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(glGetUniformLocation(objectShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
				// Set Model
				glBindVertexArray(awesomeVAO);
		
				glDrawArrays(GL_TRIANGLES, 0, 36);
		#pragma endregion

		#pragma region light object
				// Set Model matrix
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[3]);
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

				// Set View and Projection Matrices here if you want.
				//

				// Set Material -> Shader Program
				lightShader.use();										//先使用shader才能改变uniform的值
				// Set Material -> Textures
				//
				// Set Material -> Uniforms
				glUniform3f(glGetUniformLocation(lightShader.ID, "lightColor"), 1.0f, 1.0f, 1.0f);
				glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

				// Set Model
				glBindVertexArray(lightVAO);

				glDrawArrays(GL_TRIANGLES, 0, 36);
		#pragma endregion

		#pragma region color object
				// Set Model matrix
				model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[2]);
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				// Set View and Projection Matrices here if you want.
				//

				// mormal change 
				glm::mat3 normalChange = glm::mat3(transpose(inverse(model)));

				// Set Material -> Shader Program
				colorShader.use();										//先使用shader才能改变uniform的值
				// Set Material -> Textures
				//
				// Set Material -> Uniforms
				glUniform3f(glGetUniformLocation(colorShader.ID, "objectColor"), 1.0f, 0.5f, 0.31f);
				colorShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
				//glUniform3fv(glGetUniformLocation(colorShader.ID, "lightColor"), 1, &glm::vec3(1.0f, 1.0f, 1.0f)[1]);
				colorShader.setVec3("lightPos", cubePositions[3]);
				colorShader.setMat3("normalChange", normalChange);
				colorShader.setVec3("viewPos", ourCamera->cameraPos);
				glUniformMatrix4fv(glGetUniformLocation(colorShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glUniformMatrix4fv(glGetUniformLocation(colorShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
				glUniformMatrix4fv(glGetUniformLocation(colorShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

				// Set Model
				glBindVertexArray(lightVAO);

				glDrawArrays(GL_TRIANGLES, 0, 36);
		#pragma endregion

		
		//glBindVertexArray(lightVAO);
		glBindVertexArray(0);

		//监测事件，交换缓冲
		glfwSwapBuffers(window_1);
		glfwPollEvents();
	}
	// 清理资源 
	glfwTerminate();
	return 0;              
}



/******************************************************
*******************************************************
******************************************************/

