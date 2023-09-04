workspace "CPURayTracer"
    architecture "x86_64"
    startproject "CPURayTracer"

    configurations
    {
        "Debug",
        "Release"
    }

    sourcedir = "./src"
    vendordir = "./vendor"
    outputdir = "%{cfg.buildcfg}_%{cfg.system}_%{cfg.architecture}"

    include "CPURayTracer"

newaction
{
    trigger = "clean",
    description = "Remove all binaries, intermediate binaries, and VS Files.",
    execute = function()
        print("Removing binaries & intermediate binaries")
        os.rmdir("./CPURayTracer/build")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}