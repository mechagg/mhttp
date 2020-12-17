workspace "mhttp"
    architecture "x86"

    flags
    {
        "MultiProcessorCompile"
    }

    configurations
    {
        "Debug",
        "Release",
    }

options = {
    output_directory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}",
}

includes = {
    libcurl   = "%{wks.location}/third_party/curl/include",
    mhttp     = "%{wks.location}/mhttp/src",
    garrysmod = "%{wks.location}/third_party/garrysmod/include",
}

group "thirdparty"
    include "third_party/curl"
group ""

include "module"
include "mhttp"
