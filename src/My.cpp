#include "My.h"




//读取用户输入并且行动的函数
void My::processInput(GLFWwindow* window,Camera camera)
{
	float moveSpeed = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		moveSpeed = 10.0f;
	}
	else
	{
		moveSpeed = 1.0f;
	}

	//前后移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.SpeedZ = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.SpeedZ = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedZ = 0;
	}
	//左右移动
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.SpeedX = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.SpeedX = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedX = 0;
	}
	//上下移动
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.SpeedY = 1.0f * moveSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera.SpeedY = -1.0f * moveSpeed;
	}
	else
	{
		camera.SpeedY = 0;
	}
	//隐藏鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}