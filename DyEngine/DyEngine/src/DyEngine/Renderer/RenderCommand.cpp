#include "DyPch.h"
#include "RenderCommand.h"

#include "Platform/Opengl/OpenglRendererAPI.h"

namespace DyEngine
{
	/**
	 * \brief —°‘ÒAPI
	 */
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}