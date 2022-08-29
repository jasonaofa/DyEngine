#include "DyPch.h"
#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Renderer.h"

namespace DyEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None		:	DY_CORE_ASSERT(false, "RendererAPI::None"); return nullptr;
			case RendererAPI::API::OpenGL	:	return new OpenGLVertexBuffer(vertices,size);
		}
		DY_CORE_ASSERT(false,"Unknown API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None		:	DY_CORE_ASSERT(false, "RendererAPI::None"); return nullptr;
			case RendererAPI::API::OpenGL		:	return new OpenGLIndexBuffer(indices, size);
		}
		DY_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}
