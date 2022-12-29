#include "DyPch.h"
#include "Model.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLModel.h"

namespace DyEngine
{
	Ref<Model> Model::Create(std::string path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLModel>(path);
		}

		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
