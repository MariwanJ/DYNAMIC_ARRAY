workspace "prj1"
    configurations
    {
        "Debug",
        "Release"
    }

    architecture "x86_64"


project "prj1"
    language "C"
    kind "ConsoleApp"

    targetdir ("bin/%{prj.name}")
    objdir ("bin-int/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.c"
    }

    includedirs
    {
        "src"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines
        {
            "PLATFORM_WINDOWS"
        }

        links
        {

        }

    filter "system:linux"
        buildoptions
        {
            "-std=c2x"
        }

        defines
        {
            "PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}


project "tests"
    language "C"
    kind "ConsoleApp"

    targetdir ("bin/%{prj.name}")
    objdir ("bin-int/%{prj.name}")

    files
    {
        "tests/**.c",
        "src/*.h"
    }

    includedirs
    {
        "src"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

        defines
        {
            "PLATFORM_WINDOWS"
        }

        links
        {
            "Comctl32.lib",
            "Ws2_32.lib",
            "Gdiplus.lib"
        }

    filter "system:linux"
        buildoptions
        {
            "-std=c2x"
        }

        defines
        {
            "PLATFORM_LINUX"
        }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"

    filter {}