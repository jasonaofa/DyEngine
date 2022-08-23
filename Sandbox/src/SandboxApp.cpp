#include <DyEngine.h>

#include "imgui.h"

class ExamplerLayer : public DyEngine::Layer
{
public:
	ExamplerLayer()
		:Layer("Example")
	{

	}
	void OnUpdate() override
	{
		//DY_INFO("ExamplerLayer::Update");
		if (DyEngine::Input::IsKeyPressed(DY_KEY_TAB))
		{
			DY_INFO("Tab is pressed!");
		}

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("test");
		ImGui::Text("testText");
		ImGui::End();
	}

	void OnEvent(DyEngine::Event& event) override
	{
		//输出所有事件
		//DY_TRACE("{0}", event);
	}

};

class Sandbox : public DyEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExamplerLayer());
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