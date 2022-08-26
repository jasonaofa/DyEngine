#include "DyPch.h"

#include "DyEngine/Events/ApplicationEvent.h"

#include "DyEngine/Log.h"
#include "Application.h"
#include <glad/glad.h>
#include "imgui_impl_opengl3_loader.h"
#include "DyEngine/Renderer/Renderer.h"

#include <glfw/glfw3.h>

#include "Input.h"


namespace DyEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DY_CORE_ASSERT(!s_Instance,"Application already exists!")
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray = VertexArray::Create();


		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f, 0.8f,0.2f,0.8f,1.0f,
			0.5f,-0.5f,0.0f,0.2f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.8f,0.8f,0.2f,1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		


		unsigned int indices[3] = { 0,1,2, };
		m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		const std::string vertexSrc = R"(
			#version 330 core
			layout(location =0) in vec3 a_Position;
			layout(location =1) in vec4 a_Color;

			out vec3 v_Position;
			out	vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = vec4(a_Position,1.0f);
			}
		)";


		const std::string fragmentSrc = R"(
			#version 330 core
			layout(location =0) out vec4 color;

			in  vec3 v_Position;
			in	vec4 v_Color;
			void main()
			{
				color = vec4(0.8,0.2,0.3,1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	}

	Application::~Application()
	{
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();


			//遍历
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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
}
