#include "DyPch.h"
#include "Environment.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLEnvironment.h"

namespace DyEngine
{
	static Environment::EnvData m_EnvData;

	Ref<Environment> Environment::Create(EnvData& env_data, Ref<Shader>& env_shader)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLEnvironment>(env_data, env_shader);
		}

		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Environment::SunStats Environment::GetSunStats()
	{
		return m_EnvData.sunData;
	}
}
