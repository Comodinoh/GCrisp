project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir {"bin/" .. outputdir .. "/%{prj.name}"}
    objdir {"bin-int/" .. outputdir .. "/%{prj.name}"}

    files
    {
        "include/**.h",
        "src/**.c"
    }

    includedirs
    {
        "include"
    }
