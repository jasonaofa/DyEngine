#pragma once

#include"DyEngine/Layer.h"
#include "DyEngine/Events/MouseEvent.h"
#include "DyEngine/Events/KeyEvent.h"
#include "DyEngine/Events/ApplicationEvent.h"

namespace DyEngine
{
	class DLLEXPORT ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();

		void SetDarkThemeColors();
	private:
		float m_Time = 0.0f;

	};
};
