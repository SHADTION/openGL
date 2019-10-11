#version 330 core
out vec4 FragColor;

//in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture2;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
	//FragColor = mix(texture(texture0, texCoord), texture(texture2, texCoord), 0.2); //* vec4(ourColor, 1.0f);
}