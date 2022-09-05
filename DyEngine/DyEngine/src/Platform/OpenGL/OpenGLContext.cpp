#include "DyPch.h"

#include "glad/glad.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>


namespace DyEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		DY_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);

		//这是初始化GLAD
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
		{
			std::cout << "Failed to initialize Glad!" << std::endl;
		};
		DY_CORE_INFO("OpenGL Info:");
		DY_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		DY_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		DY_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		if (GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5))
		{
			std::cout << "DyEngine requires at least OpenGL version 4.5!" << std::endl;
		};
	}

	void OpenGLContext::SwapBuffers()
	{
		DY_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
