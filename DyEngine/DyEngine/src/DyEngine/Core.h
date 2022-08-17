#pragma once

#ifdef DY_PLATFORM_WINDOWS
	#ifdef DY_BUILD_DLL
		#define DLLEXPORT __declspec(dllexport)
	#else
		#define DLLEXPORT __declspec(dllimport)
	#endif
#else
	#error Dy only supports windows!
#endif

#ifdef DY_ENABLE_ASSERTS
	#define DY_ASSERT(x,...){if(!(x)){DyEngine_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
	#define DY_CORE_ASSERT(x,...){if(!(x)){DyEngine_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
#else
	#define DY_ASSERT(x,...)
	#define DY_CORE_ASSERT(x,...)
#endif 




//让enum的值不只等于赋给他的值，还等于小一位的值
//比如
//EventCategorMouse			= BIT(3),
//EventCategorMoustButton	= BIT(4)
//那么MoustButton既是4又是3
#define BIT(x) (1 << x)

namespace DyEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


}
