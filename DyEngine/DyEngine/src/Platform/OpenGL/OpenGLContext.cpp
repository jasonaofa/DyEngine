#include "DyPch.h"

#include "OpenGLContext.h"

#include "DyEngine/Log.h"
#include "glad/glad.h"


namespace DyEngine
{

	 OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		 :m_WindowHandle(windowHandle)
	{
	}

	 void OpenGLContext::Init()
	{
		 glfwMakeContextCurrent(m_WindowHandle);

		 DY_CORE_INFO("OpenGL Info:");
		 DY_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		 DY_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		 DY_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	 void OpenGLContext::SwapBuffers()
	{
		 glfwSwapBuffers(m_WindowHandle);
	}
}
