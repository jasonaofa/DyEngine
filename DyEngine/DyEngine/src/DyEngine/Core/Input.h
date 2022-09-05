#pragma once
#include "Base.h"
namespace  DyEngine
{
	/**
	 * \brief 不用在每一次Update中去判定是否有时间，可以直接生成事件
	 */
	class Input
	{
	public:
		//public 静态从恒源函数提供接口，以访问protected纯虚函数，具体的函数功能实现由派生类重写
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode);}

		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button);}
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl();}

		static float GetMouseX() { return s_Instance->GetMouseXImpl();}
		static float GetMouseY() { return s_Instance->GetMouseYImpl();}

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;



	private:
		static Scope<Input> s_Instance;

	};

}
