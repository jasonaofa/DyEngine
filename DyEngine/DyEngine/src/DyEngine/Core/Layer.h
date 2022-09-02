#pragma once
#include "Timestep.h"
#include "Core.h"
#include "DyEngine/Events/Event.h"

namespace  DyEngine
{
	/**
	 * \brief layer的抽象类
	 */
	class DLLEXPORT Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


