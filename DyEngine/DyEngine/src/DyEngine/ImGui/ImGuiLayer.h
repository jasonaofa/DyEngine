#pragma once

#include"DyEngine/Layer.h"

namespace DyEngine
{
	class DLLEXPORT ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();

	private:
		float m_Time;

	};
};
