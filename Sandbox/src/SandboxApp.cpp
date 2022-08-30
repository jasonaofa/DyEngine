#include <DyEngine.h>
#include "imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
class ExamplerLayer : public DyEngine::Layer
{
public:
	ExamplerLayer()
		:Layer("Example"),m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0)
	{

		m_VertexArray.reset(DyEngine::VertexArray::Create());


		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		//float vertices[5 * 4] = {
		//	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		//	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		//	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		//	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
		//};

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

		const std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";


		const std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;
			uniform vec3 u_Color;

			void main()
			{
				//color = vec4(v_TexCoord,0,0);
				color = texture(u_Texture, v_TexCoord);
				color *=vec4(u_Color,1);
			}
		)";
		m_TextureShader.reset(DyEngine::Shader::Create(vertexSrc, fragmentSrc));

		m_Texture = DyEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_ChernoLogoTexture = DyEngine::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}
	void OnUpdate(DyEngine::Timestep deltaTime) override
	{
		DY_TRACE("Delta Time:{0}s,({1}ms)", deltaTime.GetSeconds(),deltaTime.GetMilliseconds());
		if (DyEngine::Input::IsKeyPressed(DY_KEY_LEFT) )
		{
			m_CameraPosition.x -= m_CameraMoveSpeed *deltaTime ;
		}
		else if (DyEngine::Input::IsKeyPressed(DY_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		}
		if (DyEngine::Input::IsKeyPressed(DY_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed* deltaTime;
		}
		else if (DyEngine::Input::IsKeyPressed(DY_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed* deltaTime;
		}

		if (DyEngine::Input::IsKeyPressed(DY_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed* deltaTime;
		}
		if (DyEngine::Input::IsKeyPressed(DY_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed* deltaTime;
		}



		DyEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		DyEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		//glm::mat4 transform = glm::translate(glm::mat4(0.5f), glm::vec3(0.5f));
		DyEngine::Renderer::BeginScene(m_Camera);

		//DyEngine::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
		std::dynamic_pointer_cast<DyEngine::OpenGLShader>(m_TextureShader)->UploadUniformFloat3("u_Color", m_TriColor);


		m_Texture->Bind();
		DyEngine::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
		m_ChernoLogoTexture->Bind();
		DyEngine::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));


		//for (int y = 0; y < 20; y++)
		//{
		//	for (int x = 0; x < 20; x++)
		//	{
		//		glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
		//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		//		DyEngine::Renderer::Submit(m_Shader, m_VertexArray, transform);
		//	}
		//}
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

		//输出所有事件
		//DY_TRACE("{0}", event);
	}

private:
	DyEngine::Ref<DyEngine::Shader> m_Shader;
	DyEngine::Ref<DyEngine::Shader> m_TextureShader;

	DyEngine::Ref<DyEngine::Texture2D> m_Texture, m_ChernoLogoTexture;
	DyEngine::Ref<DyEngine::VertexArray> m_VertexArray;

	DyEngine::Ref<DyEngine::VertexBuffer> m_VertexBuffer;
	DyEngine::Ref<DyEngine::IndexBuffer> m_IndexBuffer;

	DyEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 10.0f;

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