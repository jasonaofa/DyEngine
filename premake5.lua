workspace "DyEngine"
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


	include"DyEngine/vendor/glfw"
	include"DyEngine/vendor/Glad"

project"DyEngine"
	location"DyEngine"
	kind"SharedLib"
	language"C++"

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
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"Glad",
		"GLFW.lib",
		"opengl32.lib"
	}
	filter "system:windows"
		cppdialect		"C++17"	
		staticruntime	"On"
		systemversion	"latest"

		defines	
		{
			"DY_ENABLE_ASSERTS",
			"DY_PLATFORM_WINDOWS",
			"DY_BUILD_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		buildoptions "/MDd"
		symbols "On"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		buildoptions "/MD"
		optimize "On"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		buildoptions "/MD"
		optimize "On"	
	
project"SandBox"
	location"SandBox"
	kind "ConsoleApp"
	language"C++"

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
		staticruntime	"On"
		systemversion	"latest"

		defines	
		{
			"DY_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		buildoptions "/MDd"
		symbols "On"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		buildoptions "/MD"
		optimize "On"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		buildoptions "/MDd"
		optimize "On"	