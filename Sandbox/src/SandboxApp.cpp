#include <DyEngine.h>
#include <DyEngine/Core/EntryPoint.h>
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ExampleLayer.h"
#include "Sandbox2D.h"


class Sandbox : public DyEngine::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{
		
	}
};

//-----------自定义的入口-----------------
DyEngine::Application* DyEngine::CreateApplication()
{
	return new Sandbox();
}