#pragma once

#include "DyEngine/Renderer/Shader.h"

namespace DyEngine {
	enum class RendererAPI
	{
		None =0,OpenGL =1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;

		//static void Init();
		//static void Shutdown();

		//static void OnWindowResize(uint32_t width, uint32_t height);

		//static void BeginScene(OrthographicCamera& camera);
		//static void EndScene();

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