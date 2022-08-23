#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "DyEngine/LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "DyEngine/ImGui/ImGuiLayer.h"

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

		inline static Application& Get(){return *s_Instance;}


		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
	
}


