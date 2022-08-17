#include "DyPch.h"
#include "Log.h"


namespace DyEngine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClintLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("DyEngine");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClintLogger = spdlog::stdout_color_mt("APP");
		s_ClintLogger->set_level(spdlog::level::trace);

	}
}

