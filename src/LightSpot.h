#pragma once
#include <glm.hpp>

class LightSpot
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 color;
	glm::vec3 direction = glm::vec3(0,0,1.0f);

	float constant;
	float linear;
	float quadratic;

	float cosPhiInner = 0.9f;
	float cosPhiOuter = 0.85f;

	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f,1.0f,1.0f));
	void UpdateDirection();
};
