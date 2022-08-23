#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>
#include "Renderer/GraphicsContext.h"



namespace DyEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:


		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}
