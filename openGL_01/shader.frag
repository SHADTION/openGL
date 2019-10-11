#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture2;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
	FragColor = mix(texture(texture0, texCoord), texture(texture2, texCoord), 0.2); //* vec4(ourColor, 1.0f);
}