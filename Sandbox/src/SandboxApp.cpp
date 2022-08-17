#include <DyEngine.h>

class ExamplerLayer : public DyEngine::Layer
{
public:
	ExamplerLayer()
		:Layer("Example")
	{

	}
	void OnUpdate() override
	{
		DyEngine_INFO("ExamplerLayer::Update");
	}

	void OnEvent(DyEngine::Event& event) override
	{
		DyEngine_TRACE("{0}", event);
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