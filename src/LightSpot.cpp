#include "LightSpot.h"

#include <gtx/rotate_vector.hpp>

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position), angles(_angles), color(_color)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	//更新灯光的方向，默认是朝向屏幕外，根据给的angles来让灯光旋转
	//因为shader中的方向向量都是从片元向外的，所以这里直接乘-1，shader里就不用取反了
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateY(direction, angles.y);
	direction = glm::rotateX(direction, angles.x);
	direction *= -1.0f;
}