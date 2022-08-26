#pragma once


#include "glm/vec4.hpp"
#include "VertexArray.h"

namespace DyEngine
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,DirectX = 2
		};
	public:
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		inline static API GetApi() { return s_API; }
	private:
		static API s_API;
	};
}
