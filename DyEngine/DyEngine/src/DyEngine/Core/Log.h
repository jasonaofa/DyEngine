#pragma once
#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace DyEngine
{
	class DLLEXPORT Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClintLogger() { return s_ClintLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClintLogger;


	};
}

//Core log MACROS
#define DY_CORE_ERROR(...)	::DyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DY_CORE_WARN(...)		::DyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DY_CORE_INFO(...)		::DyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DY_CORE_TRACE(...)	::DyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DY_CORE_FATAL(...)	::DyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Core Clint macros
#define DY_ERROR(...)		::DyEngine::Log::GetClintLogger()->error(__VA_ARGS__)
#define DY_WARN(...)		::DyEngine::Log::GetClintLogger()->warn(__VA_ARGS__)
#define DY_INFO(...)		::DyEngine::Log::GetClintLogger()->info(__VA_ARGS__)
#define DY_TRACE(...)		::DyEngine::Log::GetClintLogger()->trace(__VA_ARGS__)
#define DY_FATAL(...)		::DyEngine::Log::GetClintLogger()->fatal(__VA_ARGS__)
