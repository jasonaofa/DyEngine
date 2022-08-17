#include "DyPch.h"
#include "DyEngine/Events/ApplicationEvent.h"
#include "DyEngine/Log.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace DyEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//如果事件是WindowCloseEvent，就调用OnWindowClose函数
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		//this is DyEngine get the event NOT app get event
		//TODO delete later
		//DyEngine_CORE_TRACE("{0}", e);
		//反向遍历
		for(auto it = m_LayerStack.end();it !=m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}



	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			//遍历
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
