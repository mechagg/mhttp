project "libcurl"
    language "C"
    kind "StaticLib"
    staticruntime "On"
    warnings "Off"

    targetdir ("%{wks.location}/bin/" .. options.output_directory .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. options.output_directory .. "/%{prj.name}")

    defines 
    { 
        "BUILDING_LIBCURL", 
        "CURL_STATICLIB", 
        "HTTP_ONLY",
    }
  
    files 
    {
		"lib/**.h",
		"lib/**.c",
        "include/**.h",
	}

    includedirs 
    {
        "include", 
        "lib"
    }

    filter "system:windows"
		defines 
        { 
            "USE_SCHANNEL", 
            "USE_WINDOWS_SSPI" 
        }

		links "crypt32"
