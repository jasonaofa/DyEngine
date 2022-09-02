#pragma once

#include "Core.h"
#include "DyEngine/Events/Event.h"
#include "Log.h"

namespace DyEngine
{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		//Tags 窗口尺寸
		WindowProps(const std::string& title = "DyEngine",
					unsigned int width = 1280,
					unsigned int height = 1280)
						:Title(title),Width(width),Height(height)
		{
		}
	};

	class DLLEXPORT Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};








}
