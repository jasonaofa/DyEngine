#pragma once
#include "DyEngine/Renderer/Environment.h"

namespace DyEngine
{
	class OpenGLEnvironment : public Environment
	{
	public:
		OpenGLEnvironment(EnvData& env_data, Ref<Shader>& env_shader);
		virtual void draw() override;
		virtual ~OpenGLEnvironment(){};

	private:
		EnvData& env_data;
		Ref<Shader>& env_shader;
	};
}
