#pragma once
#include "DyEngine/Log.h"

#include "DyEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

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
