#include "DyPch.h"
#include "RenderCommand.h"

#include "Platform/Opengl/OpenglRendererAPI.h"

namespace DyEngine
{
	/**
	 * \brief ѡ��API
	 */
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}