
workspace "DyEngine"

	architecture "x86"
	startproject"SandBox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}
	
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "DyEngine/vendor/glfw/include"
	IncludeDir["Glad"] = "DyEngine/vendor/Glad/include"
	IncludeDir["ImGui"] = "DyEngine/vendor/imgui"
	IncludeDir["glm"] = "DyEngine/vendor/glm"
	IncludeDir["stb_image"] = "DyEngine/vendor/stb_image"
	IncludeDir["entt"] = "DyEngine/vendor/entt/include"
	IncludeDir["yaml_cpp"] = "DyEngine/vendor/yaml-cpp/include"

group "Dependencies"
	include"DyEngine/vendor/glfw"
	include"DyEngine/vendor/Glad"
	include"DyEngine/vendor/ImGui"
	include "DyEngine/vendor/yaml-cpp"
group""
	
project"DyEngine"
	location"DyEngine"
	kind"StaticLib"
	language"C++"
	cppdialect"C++17"	
	staticruntime"on"

	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	pchheader"DyPch.h"
	pchsource"DyEngine/DyEngine/src/DyPch.cpp"

	files
	{
		"DyEngine/DyEngine/src/**.h",
		"DyEngine/DyEngine/src/**.c",
		"DyEngine/DyEngine/src/**.cpp",
		"DyEngine/vendor/glm/glm/**.hpp",
		"DyEngine/vendor/entt/include/**.hpp",
		"DyEngine/vendor/glm/glm/**.inl",
		"DyEngine/vendor/stb_image/**.h",
		"DyEngine/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"GLFW.lib",
		"yaml-cpp",
		"opengl32.lib"
	}
	filter "system:windows"
		systemversion	"latest"

		defines	
		{
			"DY_ENABLE_ASSERTS",
			"DY_PLATFORM_WINDOWS",
			"DY_BUILD_DLL",
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"

		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		runtime	"Debug"
		symbols "on"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		runtime"Release"
		optimize "on"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		runtime"Release"
		optimize "on"	
	
project"SandBox"
	location"SandBox"
	kind "ConsoleApp"
	language"C++"
	cppdialect"C++17"	
	staticruntime"on"


	targetdir("bin/" .. outputdir .."/%{prj.name}")
	objdir("bin-int/" .. outputdir .."/%{prj.name}")

	files
	{
		"SandBox/src/**.h",
		"SandBox/src/**.c",
		"SandBox/src/**.cpp",
		"SandBox/Assets/Shaders/**.glsl",
		"SandBox/Assets/Textures/**.png",
		"SandBox/**.ini",
		"SandBox/**.json",

	}

	includedirs
	{
		"DyEngine/vendor/Glad/include;",
		"DyEngine/DyEngine/src;",
		"DyEngine/vendor/spdlog/include;",
		"DyEngine/vendor/imgui;",
		"DyEngine/vendor/glfw/include;",
		"DyEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"DyEngine"
	}

	filter "system:windows"
		systemversion	"latest"

		defines	
		{
			"DY_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		runtime"Debug"
		symbols "on"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		runtime"Release"
		optimize "on"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		runtime"Release"
		optimize "on"	



project "DY-Editor"
	location "DY-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/**.ini",
		"%{prj.name}/**.glsl",
		"%{prj.name}/**.png",
		"%{prj.name}/**.dy"
	}

	includedirs
	{
		"DyEngine/vendor/Glad/include;",
		"DyEngine/DyEngine/src;",
		"DyEngine/vendor/spdlog/include;",
		"DyEngine/vendor/imgui;",
		"DyEngine/vendor/glfw/include;",
		"DyEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"DyEngine"
	}

	filter "system:windows"
		systemversion	"latest"

		defines	
		{
			"DY_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines"DyEngine_Debug"
		runtime"Debug"
		symbols "on"	

	filter "configurations:Release"
		defines"DyEngine_Release"
		runtime"Release"
		optimize "on"	

	filter "configurations:Dist"
		defines"DyEngine_Dist"
		runtime"Release"
		optimize "on"	