#pragma once

#include "DyEngine.h"

#ifdef DY_PLATFORM_WINDOWS

extern DyEngine::Application* DyEngine::CreateApplication();

int main(int argc, char** argv)
{
	DyEngine::Log::Init();
	DyEngine_CORE_INFO("Initialized Log!");
	DyEngine_INFO("Hello");

	std::cout << "Welcome to DyEngine!\n" << std::endl;
	auto app = DyEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
