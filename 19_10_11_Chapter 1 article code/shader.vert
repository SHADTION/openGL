#version 330 core
//layout (location = 10) in vec3 aPos;
//layout (location = 11) in vec3 aColor;
//layout (location = 12) in vec2 aTexCoord;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

//out vec3 ourColor;
out vec2 texCoord;

//uniform mat4 transForm;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ourColor = aColor;
	texCoord = aTexCoord;
}