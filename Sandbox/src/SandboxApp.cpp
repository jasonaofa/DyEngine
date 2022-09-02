#include <DyEngine.h>
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
class ExamplerLayer : public DyEngine::Layer
{
public:
	ExamplerLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{

		m_VertexArray.reset(DyEngine::VertexArray::Create());


		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		DyEngine::Ref<DyEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(DyEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout({
			{DyEngine::ShaderDataType::Float3,"a_Position"},
			{DyEngine::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t  indices[6] = { 0,1,2,2,3,0 };
		m_IndexBuffer.reset(DyEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_TextureShader = DyEngine::Shader::Create("Assets/Shaders/Texture.glsl");
		m_Texture = DyEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_ChernoLogoTexture = DyEngine::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}
	void OnUpdate(DyEngine::Timestep deltaTime) override
	{
		//DY_TRACE("Delta Time:{0}s,({1}ms)", deltaTime.GetSeconds(),deltaTime.GetMilliseconds());
		// Update Camera
		m_CameraController.OnUpdate(deltaTime);

		// Render
		DyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DyEngine::RenderCommand::Clear();
		DyEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		// Set Uniform
		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->UploadUniformFloat3("u_Color", m_TriColor);

		//Bindtexture and submit
		m_Texture->Bind();
		DyEngine::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
		m_ChernoLogoTexture->Bind();
		DyEngine::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		DyEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_TriColor));
		ImGui::End();
	}

	void OnEvent(DyEngine::Event& event) override
	{
		m_CameraController.OnEvent(event);
		////输出所有事件
		//DY_TRACE("{0}", event);
	}

private:
	DyEngine::Ref<DyEngine::Shader> m_Shader;
	DyEngine::Ref<DyEngine::Shader> m_TextureShader;

	DyEngine::Ref<DyEngine::Texture2D> m_Texture, m_ChernoLogoTexture;
	DyEngine::Ref<DyEngine::VertexArray> m_VertexArray;

	DyEngine::Ref<DyEngine::VertexBuffer> m_VertexBuffer;
	DyEngine::Ref<DyEngine::IndexBuffer> m_IndexBuffer;

	DyEngine::OrthographicCameraController m_CameraController;

	glm::vec3 m_TriColor = { 0.2f, 0.3f, 0.8f };
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