project "mhttp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    pchheader "mpch.hpp"
    pchsource "src/mpch.cpp"

    targetdir ("%{wks.location}/bin/" .. options.output_directory .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. options.output_directory .. "/%{prj.name}")

    defines
    {
        "CURL_STATICLIB",
    }

    files
    {
        "src/**.cpp",
        "src/**.hpp",
    }

    includedirs
    {
        "src",
    }

    filter "system:windows"
        defines
        {
            "MHTTP_WINDOWS"
        }

        systemversion "latest"
    
    filter "system:linux"
        defines
        {
            "MHTTP_LINUX"
        }

    filter "configurations:Debug"
        defines
        {
            "MHTTP_DEBUG"
        }

        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines
        {
            "MHTTP_RELEASE"
        }

        runtime "Release"
        optimize "On"