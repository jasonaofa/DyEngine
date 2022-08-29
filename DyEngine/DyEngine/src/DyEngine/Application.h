#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "DyEngine/LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "DyEngine/ImGui/ImGuiLayer.h"

#include "DyEngine/Renderer/Shader.h"
#include "DyEngine/Renderer/Buffer.h"
#include "DyEngine/Renderer/VertexArray.h"
#include "DyEngine/Renderer/OrthographicCamera.h"

namespace DyEngine
{
	class DLLEXPORT Application
	{
	public:
		Application();
		virtual ~Application() = default;

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

		std::shared_ptr<Shader> m_Shader;
		//Ref<VertexArray>  m_VertexArray;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<VertexArray> m_SquareVA;


	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
	
}


