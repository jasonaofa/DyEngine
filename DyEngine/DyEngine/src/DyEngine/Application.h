#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "DyEngine/LayerStack.h"
#include "Events/ApplicationEvent.h"

namespace DyEngine
{
	class DLLEXPORT Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
	
}


