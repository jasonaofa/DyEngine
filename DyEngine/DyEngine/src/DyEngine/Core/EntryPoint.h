#pragma once

#include "DyEngine.h"

#ifdef DY_PLATFORM_WINDOWS

extern DyEngine::Application* DyEngine::CreateApplication();

int main(int argc, char** argv)
{
	DyEngine::Log::Init();
	DY_CORE_INFO("Initialized Log!");
	DY_INFO("Hello");

	std::cout << "Welcome to DyEngine!\n" << std::endl;
	//通过实例化一个Application* 的app变量，这就是sandbox里那个执行new Sandbox的那个函数
	auto app = DyEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
