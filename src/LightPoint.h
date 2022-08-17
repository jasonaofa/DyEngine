#pragma once
#include <glm.hpp>

class LightPoint
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 lightDir;
	float constant;
	float linear;
	float quadratic;
	LightPoint(glm::vec3 _position, glm::vec3 _lightDir,glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f));
};

