﻿#pragma once
#include <memory>

#ifdef DY_PLATFORM_WINDOWS
	#if DY_DYNAMIC_LINK
		#ifdef DY_BUILD_DLL
			#define DLLEXPORT __declspec(dllexport)
		#else
			#define DLLEXPORT __declspec(dllimport)
		#endif
	#else
		#define DLLEXPORT
	#endif

#else
	#error Dy only supports windows!
#endif

#ifdef DyEngine_Debug
	#define DY_ENABLE_ASSERTS
#endif 

//USE if TO INSTEAD make "DY_ENABLE_ASSERTS 0"   WORK
#ifdef DY_ENABLE_ASSERTS
	#define DY_ASSERT(x,...){if(!(x)){DY_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
	#define DY_CORE_ASSERT(x,...){if(!(x)){DY_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
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
//bind x to placeholders
#define DY_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace DyEngine
{
	template<typename T>
	/// <summary>
	/// scope 是unique ptr
	/// </summary>
	/// <typeparam name="T"></typeparam>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	/// <summary>
	/// 用来一次性修改项目中的智能指针类型，此时ref是shared ptr
	/// </summary>
	using Ref = std::shared_ptr<T>;
}
