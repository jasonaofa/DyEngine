#pragma once
#include "DyEngine/Core/Base.h"
#include "DyEngine/Core/KeyCodes.h"
#include "DyEngine/Core/MouseCodes.h"
namespace  DyEngine
{
	/**
	 * \brief 不用在每一次Update中去判定是否有时间，可以直接生成事件
	 */
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
