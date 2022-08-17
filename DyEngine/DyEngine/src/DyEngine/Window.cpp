#include "DyPch.h"
//#include "DyEngine/Window.h"
//
//
//
//#ifdef DY_PLATFORM_WINDOWS
//	#include "Platform/Windows/WindowsWindow.h"
//#endif
//
//namespace DyEngine
//{
//	Scope<Window> Window::Create(const WindowProps& props)
//	{
//#ifdef DY_PLATFORM_WINDOWS
//		return CreateScope<WindowsWindow>(props);
//#else
//		DY_CORE_ASSERT(false, "Unknown platform!");
//		return nullptr;
//#endif
//	}
//
//}