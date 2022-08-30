#include "DyPch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace DyEngine {
	//�����ڹ��캯��
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		//����API�жϣ�Ŀǰֻ��OGL�������IGL�ͣ�makeһ��shared ptr����OpenGLTexture2D�࣬�粻�����Ǿ�������󣬲��ҷ��ؿ�ָ�롣
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    DY_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  DY_CORE_INFO("Created OpenGLTexture2D !"); return std::make_shared<OpenGLTexture2D>(path);
		}
		//������е�����Ǿͱ�Ȼ����None��OPENGL�����Է���δ֪api����������֪�������ԭ��
		DY_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}