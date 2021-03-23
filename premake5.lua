workspace "Prometheus"
	architecture "x64"
	startproject "Prometheus-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Prometheus/vendor/GLFW/include"
IncludeDir["Glad"] = "Prometheus/vendor/Glad/include"
IncludeDir["ImGui"] = "Prometheus/vendor/imgui"
IncludeDir["glm"] = "Prometheus/vendor/glm"
IncludeDir["stb_image"] = "Prometheus/vendor/stb_image"
IncludeDir["entt"] = "Prometheus/vendor/entt/include"

group "Dependencies"
	include "Prometheus/vendor/GLFW"
	include "Prometheus/vendor/Glad"
	include "Prometheus/vendor/imgui"

group ""

project "Prometheus"
	location "Prometheus"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pmpch.h"
	pchsource "Prometheus/src/pmpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"PM_PLATFORM_WINDOWS",
			"PM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines {"PM_DEBUG", "PM_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PM_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Prometheus/vendor/spdlog/include",
		"Prometheus/src",
		"Prometheus/vendor",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Prometheus"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"PM_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PM_DIST"
		runtime "Release"
		optimize "on"


project "Prometheus-Editor"
	location "Prometheus-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Prometheus/vendor/spdlog/include",
		"Prometheus/src",
		"Prometheus/vendor",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Prometheus"
	}

	filter "system:windows"
		systemversion "latest"

		defines 
		{
			"PM_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PM_DIST"
		runtime "Release"
		optimize "on"