-- premake5.lua
workspace "ParallelEngine"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "ParallelEngine-App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "ParallelEngine-Core/Build-Core.lua"
group ""

include "ParallelEngine-App/Build-App.lua"