#include "LightDirectional.h"
#include <gtx/rotate_vector.hpp>

LightDirectional::LightDirectional(glm::vec3 _position,glm::vec3 _angles, glm::vec3 _color,float _intensity):
position(_position), angles (_angles),color(_color),intensity(_intensity)
{
	UpdateDirection();
}


void LightDirectional::UpdateDirection()
{
	//更新灯光的方向，默认是朝向屏幕外，根据给的angles来让灯光旋转
	//因为shader中的方向向量都是从片元向外的，所以这里直接乘-1，shader里就不用取反了
	direction = glm::vec3(0, 0, 1.0f);
	direction = rotateX(direction, glm::radians(angles.x));
	direction = rotateZ(direction, glm::radians(angles.z));
	direction = rotateY(direction, glm::radians(angles.y));
	direction *= -1.0f;
}