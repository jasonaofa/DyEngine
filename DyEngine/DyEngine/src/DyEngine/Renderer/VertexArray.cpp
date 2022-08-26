#include "DyPch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace DyEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
