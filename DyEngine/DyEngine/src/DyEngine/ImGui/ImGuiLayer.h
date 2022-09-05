#pragma once

#include"DyEngine/Core/Layer.h"
#include "DyEngine/Events/MouseEvent.h"
#include "DyEngine/Events/KeyEvent.h"
#include "DyEngine/Events/ApplicationEvent.h"

namespace DyEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void Begin();
		void End();

		void SetDarkThemeColors();
	private:
		float m_Time = 0.0f;

	};
};
