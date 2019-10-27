#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
}; 

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint {
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
    float linear;
    float quadratic;
};

struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
	float constant;
    float linear;
    float quadratic;
	float thetaIn;
	float thetaOut;
};

uniform Material material;
uniform LightDirectional lightD;
uniform LightPoint lightP0;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightSpot lightS;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 viewPos;
uniform vec3 objectColor;

out vec4 FragColor;

vec3 CalcLightDirectional(LightDirectional light, vec3 normal, vec3 dirToCamera){

	// diffuse   max( dot( L, N), 0)
	float diffIntensity = max( dot( light.dirToLight, normal), 0);
	vec3 diffColor = diffIntensity * light.color * texture( material.diffuse, TexCoord).rgb;

	// specular   pow( max( dot( R, toCamera), 0), shininess)
	vec3 R = normalize( reflect( -light.dirToLight, normal));
	float specIntensity = pow( max( dot( R, dirToCamera), 0), material.shininess);
	vec3 specColor = specIntensity * light.color * texture( material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor; 
	return result;

}

vec3 CalcLightPoint(LightPoint light, vec3 normal, vec3 dirToCamera){

	// attenuation
	float dist = length( light.pos - FragPos);
	float attenuation = 1 / ( light.constant + light.linear * dist + light.quadratic * ( dist * dist ));

	// diffues
	float diffIntensity = max( dot( normalize( light.pos - FragPos), normal), 0) * attenuation;
	vec3 diffColor = diffIntensity * light.color * texture( material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize( reflect( -normalize( light.pos - FragPos), normal));
	float specIntensity = pow( max( dot( R, dirToCamera), 0), material.shininess) * attenuation;
	vec3 specColor = specIntensity * light.color * texture( material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

vec3 CalcLightSpot(LightSpot light, vec3 normal, vec3 dirToCamera){

	// attenuation
	float dist = length( light.pos - FragPos);
	float attenuation = 1 / ( light.constant + light.linear * dist + light.quadratic * ( dist * dist ));

	// spot ratio
	float theta = dot( normalize( light.pos - FragPos), -light.dirToLight);

	float spotDate;
	if(theta > lightS.thetaIn)	//	光圈内
		spotDate = 1.0f;
	else if(theta > lightS.thetaOut)	//	边缘
		spotDate = (theta - lightS.thetaOut) / (lightS.thetaIn - lightS.thetaOut);
		//spotDate = 0.5f;
	else	//	外面
		spotDate = 0;

	// diffues
	float diffIntensity = max( dot( normalize( light.pos - FragPos), normal), 0) * attenuation * spotDate;
	vec3 diffColor = diffIntensity * light.color * texture( material.diffuse, TexCoord).rgb;

	// specular
	vec3 R = normalize( reflect( -normalize( light.pos - FragPos), normal));
	float specIntensity = pow( max( dot( R, dirToCamera), 0), material.shininess) * attenuation * spotDate;
	vec3 specColor = specIntensity * light.color * texture( material.specular, TexCoord).rgb;

	vec3 result = diffColor + specColor;
	return result;
}

void main()
{
	vec3 finalResult;
	vec3 uNormal = normalize(Normal);
	vec3 dirToCamera = normalize(viewPos - FragPos);


	finalResult += CalcLightDirectional(lightD, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP0, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP1, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP2, uNormal, dirToCamera);
	finalResult += CalcLightPoint(lightP3, uNormal, dirToCamera);
	finalResult += CalcLightSpot(lightS, uNormal, dirToCamera);

	//out fragcolor
    FragColor = vec4(finalResult, 1.0);
}
