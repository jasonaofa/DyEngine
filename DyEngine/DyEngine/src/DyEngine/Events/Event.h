#pragma once

#include "DyEngine/Core/Core.h"


namespace DyEngine
{
	//从0开始，到14结束
	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	//分类一下
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	/**
 * \brief 
 * \param type 具体是什么类型的事件
 */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
	/**
 * \brief 
 * \param category 大致的事件类型
 */
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/**
	 * \brief 所有事件的基类
	 */
	class Event
	{
	public:
		virtual ~Event() = default;

		//用来记录event是否被handle的flag
		bool Handled = false;

		//纯虚函数，没有初始化，必须在派生类中再写一遍

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		//用来查是哪一类event
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};


	/**
	 * \brief 调度器/分发器 根据事件类型调度事件
	 *	example:
	 *	  EventDispatcher dispatcher(event);
		  dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));


		  dispatcher.Dispatch<用来判断的时间类型是否和创建的时候给的event一致>（如果一致就执行这里面的代码）

	 */
	class EventDispatcher
	{
	public:
		/**
		 * \brief 把事件绑定到调度器上
		 * \param event 
		 */
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}










