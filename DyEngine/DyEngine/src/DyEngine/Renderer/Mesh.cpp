#include "DyPch.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenglMesh.h"


namespace DyEngine
{
	Ref<Mesh> Create(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<meshTexture> textures)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMesh>(vertices, indices, textures);
		}

		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}



}
