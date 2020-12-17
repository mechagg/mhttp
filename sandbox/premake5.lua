project "sandbox"
    kind "ConsoleApp"
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
        "%{includes.mhttp}",
        "%{includes.libcurl}",
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"