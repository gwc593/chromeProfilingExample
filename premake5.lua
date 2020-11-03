workspace "MergeSort"
	architecture "x86"
	
	configurations
	{
		"Debug",
		"Profiling",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

LibDirs = {}

-------------------------------------------------------
--------- Test Harness ---------------------------------
-------------------------------------------------------	
	project "sortProfiling"

	location""
	kind "ConsoleApp"
	
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	
	files
	{
		"./include/**.h",
		"./include/**.hpp",
		"./src/**.cpp"

	}

	includedirs
	{
		"./src",
		"./include"
	}
	
	libdirs
	{

	}
	
	links
	{
		
	}

	filter "system:windows"
		systemversion "latest"

	defines
	{
	}
	
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines{}
		

	filter "configurations:Release"
		defines{"NDEBUG"}
		runtime "Release"
		optimize "on"

