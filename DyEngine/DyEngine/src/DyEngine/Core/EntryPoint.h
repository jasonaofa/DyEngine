#pragma once

#include "DyEngine.h"

#ifdef DY_PLATFORM_WINDOWS

extern DyEngine::Application* DyEngine::CreateApplication();

int main(int argc, char** argv)
{
	DyEngine::Log::Init();
	DY_CORE_INFO("Initialized Log!");
	DY_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = DyEngine::CreateApplication();
	DY_PROFILE_END_SESSION();

	DY_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	DY_PROFILE_END_SESSION();

	DY_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
	delete app;
	DY_PROFILE_END_SESSION();
}

#endif
