#include "Material.h"



Material::Material(Shader* Shader, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float Shininess):
	shader(Shader), 
	ambient(Ambient), 
	diffuse(Diffuse), 
	specular(Specular), 
	shininess(Shininess)
{
}

Material::~Material()
{
}
