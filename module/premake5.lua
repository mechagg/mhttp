project "module"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

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

    links
    {
        "mhttp",
    }

    includedirs
    {
        "src",
        "%{includes.libcurl}",
        "%{includes.mhttp}",
        "%{includes.garrysmod}",
    }

    filter "system:windows"
        defines
        {
            "MHTTP_WINDOWS"
        }

        systemversion "latest"
        targetname "gmsv_mhttp_win32"
    
    filter "system:linux"
        defines
        {
            "MHTTP_LINUX"
        }

        targetname "gmsv_mhttp_linux"

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