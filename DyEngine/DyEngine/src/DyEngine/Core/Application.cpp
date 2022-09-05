#include "DyPch.h"

#include "DyEngine/Events/ApplicationEvent.h"

#include "Log.h"
#include "Application.h"
#include <glad/glad.h>
#include "imgui_impl_opengl3_loader.h"
#include "DyEngine/Renderer/Renderer.h"


#include <glfw/glfw3.h>

#include "Input.h"


namespace DyEngine
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DY_CORE_ASSERT(!s_Instance,"Application already exists!")
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(DY_BIND_EVENT_FN(Application::OnEvent));
		m_Window->SetVSync(false);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//如果事件是WindowCloseEvent，就调用OnWindowClose函数
		dispatcher.Dispatch<WindowCloseEvent>(DY_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(DY_BIND_EVENT_FN(Application::OnWindowResize));
		//this is DyEngine get the event NOT app get event
		//TODO delete later
		//DY_CORE_TRACE("{0}", e);
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
			float time = (float)glfwGetTime();//should be Platform::GetTime;
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;


			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			//C++17 结构化绑定的演示
			//auto [x, y] = Input::GetMousePosition();
			//DY_CORE_TRACE("{0},{1}",x,y );
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	/**
	 * \brief 重置窗口
	 * \param e 
	 * \return 
	 */
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
