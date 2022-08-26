#pragma once

#include "DyEngine/Renderer/Shader.h"
#include "RenderCommand.h"
namespace DyEngine {


	class Renderer
	{
	public:

		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }		//static void Init();
		//static void Shutdown();

		//static void OnWindowResize(uint32_t width, uint32_t height);




		//static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		//static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		//struct SceneData
		//{
		//	glm::mat4 ViewProjectionMatrix;
		//};

		//static Scope<SceneData> s_SceneData;
	};

}