project "CPURayTracer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("./build/bin/" .. outputdir .. "/%{prj.name}")
    objdir("./build/obj/" .. outputdir .. "/%{prj.name}")

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    files 
    {
        sourcedir .. "/**.cpp",
        sourcedir .. "/**.h"
    }

    includedirs 
    {
        sourcedir
    }

    filter { "configurations:Debug" }
        buildoptions "/MTd"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        defines "RELEASE"
        runtime "Release"
        optimize "on"