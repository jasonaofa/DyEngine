#pragma once
#include "DyEngine/Core.h"
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
		virtual void OnUpdate(){}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}


