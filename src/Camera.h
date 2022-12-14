#pragma once
#include <glm.hpp>
#include <GLFW/glfw3.h>
#include <gtc/matrix_transform.hpp>
class Camera
{
public:

	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	/**
	 * \brief 
	 * \param position 位置
	 * \param pitch pitch角
	 * \param yaw yaw角
	 * \param worldup 世界上方向
	 */
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float offsetX, float offsetY);
	void UpdateCameraPos();
	void Inputs(GLFWwindow* window);
	//属性
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float sensitive = 0.001f;
	float SpeedZ = 0;
	float SpeedX = 0;
	float SpeedY = 0;

	float Pitch, Yaw;
private:
	void UpdateCameraVectors();
};
