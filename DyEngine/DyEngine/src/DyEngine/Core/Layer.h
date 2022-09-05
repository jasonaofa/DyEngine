#pragma once
#include "Timestep.h"
#include "Base.h"
#include "DyEngine/Events/Event.h"

namespace  DyEngine
{
	/**
	 * \brief layer的抽象类
	 */
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event){}

		const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


