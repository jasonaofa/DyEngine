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
	//���µƹ�ķ���Ĭ���ǳ�����Ļ�⣬���ݸ���angles���õƹ���ת
	//��Ϊshader�еķ����������Ǵ�ƬԪ����ģ���������ֱ�ӳ�-1��shader��Ͳ���ȡ����
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateY(direction, angles.y);
	direction = glm::rotateX(direction, angles.x);
	direction *= -1.0f;
}