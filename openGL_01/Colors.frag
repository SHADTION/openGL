#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
}; 

uniform Material material;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDir;
uniform vec3 viewPos;
uniform vec3 objectColor;

void main()
{
	// ambient
	float ambientStrength = 0.2;
    vec3 ambient = vec3(texture(material.diffuse, TexCoord)) * ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = vec3(texture(material.diffuse, TexCoord)) * diff * lightColor;

	// Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	//我们先计算视线方向与反射方向的点乘（并确保它不是负值），然后取它的32次幂。这个32是高光的反光度(Shininess)。
	//一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);	
	vec3 specular= vec3(texture(material.specular, TexCoord)) * spec * lightColor;

	//// Emission
	//float emissionStrength = 1.0;
	//vec3 emission = vec3(texture(material.emission, TexCoord)) * emissionStrength;


	vec3 result = (ambient + diffuse + specular) * objectColor;

	//out fragcolor
    FragColor = vec4(result, 1.0);
}
