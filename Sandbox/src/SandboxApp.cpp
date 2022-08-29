#include <DyEngine.h>
#include "imgui.h"


class ExamplerLayer : public DyEngine::Layer
{
public:
	ExamplerLayer()
		:Layer("Example"),m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0)
	{

		m_VertexArray.reset(DyEngine::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f, 0.8f,0.2f,0.8f,1.0f,
			0.5f,-0.5f,0.0f,0.2f,0.3f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.8f,0.8f,0.2f,1.0f,
		};

		std::shared_ptr<DyEngine::VertexBuffer> vertexBuffer;
		m_VertexBuffer.reset(DyEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		DyEngine::BufferLayout layout = {
			{DyEngine::ShaderDataType::Float3,"a_Position"},
			{DyEngine::ShaderDataType::Float4,"a_Color"}
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);



		unsigned int indices[3] = { 0,1,2, };
		m_IndexBuffer.reset(DyEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);



		const std::string vertexSrc = R"(
			#version 330 core
			layout(location =0) in vec3 a_Position;
			layout(location =1) in vec4 a_Color;

			out vec3 v_Position;
			out	vec4 v_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection*vec4(a_Position,1.0f);
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

		m_Shader.reset(new DyEngine::Shader(vertexSrc, fragmentSrc));

	}
	void OnUpdate() override
	{

		if (DyEngine::Input::IsKeyPressed(DY_KEY_LEFT) )
		{
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}
		else if (DyEngine::Input::IsKeyPressed(DY_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed;
		}
		if (DyEngine::Input::IsKeyPressed(DY_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}
		else if (DyEngine::Input::IsKeyPressed(DY_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed;
		}

		if (DyEngine::Input::IsKeyPressed(DY_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}
		if (DyEngine::Input::IsKeyPressed(DY_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}



		DyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DyEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		DyEngine::Renderer::BeginScene(m_Camera);
		DyEngine::Renderer::Submit(m_Shader, m_VertexArray);

		DyEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(DyEngine::Event& event) override
	{

		//输出所有事件
		//DY_TRACE("{0}", event);
	}

private:
	std::shared_ptr<DyEngine::Shader> m_Shader;
	std::shared_ptr<DyEngine::VertexArray> m_VertexArray;

	std::shared_ptr<DyEngine::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<DyEngine::IndexBuffer> m_IndexBuffer;

	DyEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.5f;
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