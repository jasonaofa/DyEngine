#include "DyPch.h"
#include "RenderCommand.h"

#include "Platform/Opengl/OpenglRendererAPI.h"

namespace DyEngine
{
	/**
	 * \brief 选择API
	 */
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}