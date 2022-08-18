workspace "DyEngine"

	startproject"Sandbox"
	architecture "x86"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "DyEngine/vendor/glfw/include"
	IncludeDir["Glad"] = "DyEngine/vendor/Glad/include"
	IncludeDir["ImGui"] = "DyEngine/vendor/imgui"


	include"DyEngine/vendor/glfw"
	include"DyEngine/vendor/Glad"
	include"DyEngine/vendor/ImGui"


project"DyEngine"
	location"DyEngine"
	kind"SharedLib"
	language"C++"
	staticruntime"off"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader"DyPch.h"
	pchsource"DyEngine/DyEngine/src/DyPch.cpp"

	files
	{
		"DyEngine/DyEngine/src/**.h",
		"DyEngine/DyEngine/src/**.c",
		"DyEngine/DyEngine/src/**.cpp"
	}

	libdirs 
	{
		"DyEngine/vendor/glfw/bin/Debug-windows-x86/GLFW"
	}
	includedirs
	{
		"%{prj.name}/DyEngine/src;",
		"%{prj.name}/vendor/spdlog/include;",
		"%{prj.name}/vendor/imgui;",
		"%{prj.name}/vendor/Glad;",


		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/backends",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"GLFW.lib",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect		"C++17"	
		systemversion	"latest"

		defines	
		{
			"DY_ENABLE_ASSERTS",
			"DY_PLATFORM_WINDOWS",
			"DY_BUILD_DLL"

		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandBox/\"")
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		runtime	"Debug"
		symbols "On"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		runtime"Release"
		optimize "On"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		runtime"Release"
		optimize "On"	
	
project"SandBox"
	location"SandBox"
	kind "ConsoleApp"
	language"C++"
	staticruntime"off"


	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"SandBox/src/**.h",
		"SandBox/src/**.c",
		"SandBox/src/**.cpp"

	}

	includedirs
	{
		"DyEngine/vendor/Glad/include;",
		"DyEngine/DyEngine/src;",
		"DyEngine/vendor/spdlog/include;",
		"DyEngine/vendor/imgui;",
		"DyEngine/vendor/glfw/include;",
	}

	links
	{
		"DyEngine"
	}

	filter "system:windows"
		cppdialect		"C++17"	
		systemversion	"latest"

		defines	
		{
			"DY_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		runtime"Debug"
		symbols "On"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		runtime"Release"
		optimize "On"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		runtime"Release"
		optimize "On"	