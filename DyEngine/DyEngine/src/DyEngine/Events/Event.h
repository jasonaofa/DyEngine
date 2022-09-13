#pragma once

#include "DyEngine/Core/Base.h"


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
		EventCategoryApplication	= BIT(0),//Value = 1
		EventCategoryInput			= BIT(1),//Value = 2
		EventCategoryKeyboard		= BIT(2),//Value = 4
		EventCategoryMouse			= BIT(3),//Value = 8
		EventCategoryMouseButton	= BIT(4) //Value = 16
	};

	/**
 * \brief 
 * \param type 具体是什么类型的事件
 *  "\"是续行符，表示下面那行也是同一行的
 */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
	/**
 * \brief
 * \param category 事件分类的编号
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
		/**
		 * \brief 获取具体的事件类型
		 * \return 
		 */
		virtual EventType GetEventType() const = 0;

		virtual const char* GetName() const = 0;

		/**
		 * \brief 获取事件是哪一类的（比如鼠标、按键等等）
		 * \return 
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 * \brief 转成string
		 * \return 
		 */
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


		/// <summary>
		/// 在声明一个事件调度器实例的时候，需要给一个事件，以便我们在事件调度器内判断并且执行方法
		/// </summary>
		/// <param name="event"></param>
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		/**
		 * \brief
		 *	示例：
		 *	void Application::OnEvent(Event& e)
			{
			EventDispatcher dispatcher(e);
			//如果事件是WindowCloseEvent，就调用OnWindowClose函数
			dispatcher.Dispatch<WindowCloseEvent>(DY_BIND_EVENT_FN(Application::OnWindowClose));
			}
		 * \tparam T 用来判断的事件类型
		 * \tparam F 执行的方法
		 * \param func 方法
		 * \return 
		 */
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			//如果在创建这个调度器的时候传进来的事件和我们定义的事件一致，就调用我们设定的这个函数
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










