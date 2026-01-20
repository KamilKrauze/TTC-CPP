workspace "Web-TT-Companion"
    configurations { "Debug", "Release" }
    platforms {"Linux"}
    targetdir "bin/%{cfg.buildcfg}/%{cfg.system}_%{cfg.architecture}"
    
    filter "system:linux"
        system "linux"

    filter { "system:linux", "architecture:x64" }
        architecture "x64"

    -- Linux ARM64
    filter { "system:linux", "architecture:ARM64" }
        architecture "ARM64"

    project "Server"
        kind "ConsoleApp"
        location "src"
        language "C++"
        cppdialect "C++17"
    
        targetdir "bin/%{cfg.buildcfg}"
    
        files {
            "src/**.h",
            "src/**.hpp",
            "src/**.cpp"
        }
    
        includedirs {
            "thirdparty/uWebSockets/src",
            "thirdparty/uWebSockets/uSockets/src"
        }
    
        links {
            "pthread",
            "z"
        }
    
        linkoptions {
            "thirdparty/uWebSockets/uSockets/uSockets.a"
        }
    
        prebuildcommands {
            "make -C thirdparty/uWebSockets/uSockets"
        }
  
