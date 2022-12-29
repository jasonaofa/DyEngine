#pragma once

#include "Shader.h"


namespace DyEngine
{
	class Model
	{
	public:
		static Ref<Model> Create(std::string path);
		virtual void Draw(Ref<Shader> shader) = 0;


	};

}

