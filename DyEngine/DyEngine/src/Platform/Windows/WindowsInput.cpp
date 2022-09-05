#include "DyPch.h"

#include "DyEngine/Core/Application.h"

#include <GLFW/glfw3.h>

#include "DyEngine/Core/Input.h"


namespace DyEngine
{

	/**
	 * \brief
	 * \param keycode 用来判断在激活的窗口中，按键有没有被按下或者连续按下
	 * \return
	 */
	bool Input::IsKeyPressed(KeyCode key)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos,(float)ypos };
	}



	float Input::GetMouseX()
	{

		//C++17 结构化绑定
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{

		auto [x, y] = GetMousePosition();
		return y;

	}

}
