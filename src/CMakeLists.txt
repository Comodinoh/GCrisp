set(VANE_SOURCES
        Vane/Assets/Assets.h
        Vane/Assets/AssetsManager.cpp
        Vane/Assets/AssetsManager.h
        Vane/Core/Application.cpp
        Vane/Core/Application.h
        Vane/Core/Base.h
        Vane/Core/CameraController.cpp
        Vane/Core/CameraController.cpp
        Vane/Core/CameraController.h
        Vane/Core/Core.cpp
        Vane/Core/Core.h
        Vane/Core/GWindow.h
        Vane/Core/Input.h
        Vane/Core/Layer.cpp
        Vane/Core/Layer.h
        Vane/Core/LayerStack.cpp
        Vane/Core/LayerStack.h
        Vane/Core/Log.cpp
        Vane/Core/Log.h
        Vane/Core/Memory/Allocable.h
        Vane/Core/Memory/Allocator.cpp
        Vane/Core/Memory/Allocator.h
        Vane/Core/Memory/Statistics.h
        Vane/Core/Timing.cpp
        Vane/Core/Timing.h
        Vane/Core/UUID.cpp
        Vane/Core/UUID.h
        Vane/Core/Window.cpp
        Vane/Entry.h
        Vane/Events/ApplicationEvent.h
        Vane/Events/Event.h
        Vane/Events/KeyEvent.h
        Vane/Events/MouseEvent.h
        Vane/Renderer/Buffer.cpp
        Vane/Renderer/Buffer.h
        Vane/Renderer/Camera.h
        Vane/Renderer/Context.cpp
        Vane/Renderer/Context.h
        Vane/Renderer/OrthoCamera.cpp
        Vane/Renderer/OrthoCamera.h
        Vane/Renderer/Renderer.cpp
        Vane/Renderer/Renderer.h
        Vane/Renderer/Renderer2D.cpp
        Vane/Renderer/Renderer2D.h
        Vane/Renderer/RendererBase.h
        Vane/Renderer/Shader.cpp
        Vane/Renderer/Shader.h
        Vane/Renderer/SubTexture.cpp
        Vane/Renderer/SubTexture.h
        Vane/Renderer/Texture.cpp
        Vane/Renderer/Texture.h
        Vane/Renderer/Utils.h
        Vane/Renderer/VertexArray.cpp
        Vane/Renderer/VertexArray.h
        Vane/Vane.h
)

add_library(Vane-Source STATIC ${VANE_SOURCES})

target_include_directories(Vane-Source PUBLIC .)

if (VANE_BUILD_DISTRIBUTABLE)
    target_compile_definitions(Vane-Source PUBLIC VANE_DIST=1)
    set(VANE_PROFILING OFF)
endif ()

if (VANE_PROFILING)
    target_compile_definitions(Vane-Source PUBLIC VANE_PROFILING=1)
    message(STATUS "${CMAKE_PROJECT_NAME}: Profiling enabled")
else ()
    if (VANE_FORCE_PROFILING)
        target_compile_definitions(Vane-Source PUBLIC VANE_PROFILING=1)
    endif ()
    target_compile_definitions(Vane-Source PUBLIC VANE_PROFILING=0)
    message(STATUS "${CMAKE_PROJECT_NAME}: Profiling disabled")
endif ()

target_precompile_headers(Vane-Source PUBLIC gcpch.h)
