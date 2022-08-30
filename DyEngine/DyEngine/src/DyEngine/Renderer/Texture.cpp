#include "DyPch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace DyEngine {
	//类似于构造函数
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		//先做API判断，目前只有OGL，如果是IGL就，make一个shared ptr，是OpenGLTexture2D类，如不过不是就输出错误，并且返回空指针。
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  DY_CORE_INFO("Created OpenGLTexture2D !"); return std::make_shared<OpenGLTexture2D>(path);
		}
		//如果运行到这里，那就必然不是None和OPENGL。所以返回未知api，这样可以知道错误的原因
		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}