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


	
	//Ĭ���˵ƹ���ɫ��ʵ������ʱ�򣬲������������Ҳû��
	/**
	 * \brief 
	 * \param _position �ƹ�����
	 * \param _angles �Ƕ�
	 * \param _color ��ɫ
	 */
	LightDirectional(glm::vec3 _position,glm::vec3 _angles, glm::vec3 _color ,float _intensity);

	void UpdateDirection();

};
