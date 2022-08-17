#pragma once
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0,0,1.0f);
	glm::vec3 angles;
	glm::vec3 color;
	float intensity;


	
	//默认了灯光颜色，实例化的时候，不输入这个参数也没事
	/**
	 * \brief 
	 * \param _position 灯光坐标
	 * \param _angles 角度
	 * \param _color 颜色
	 */
	LightDirectional(glm::vec3 _position,glm::vec3 _angles, glm::vec3 _color ,float _intensity);

	void UpdateDirection();

};
