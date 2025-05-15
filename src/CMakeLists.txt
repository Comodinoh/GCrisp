set(GCRISP_SOURCE GCrisp/Core/Core.h
GCrisp/Assets/Assets.h
GCrisp/Assets/AssetsManager.cpp
GCrisp/Assets/AssetsManager.h
GCrisp/Core/Application.cpp
GCrisp/Core/Timing.cpp
GCrisp/Core/Timing.h
GCrisp/Core/UUID.h
GCrisp/Core/CameraController.cpp
GCrisp/Core/CameraController.h
GCrisp/Core/Input.h
GCrisp/Core/Application.h
GCrisp/Core/LayerStack.cpp
GCrisp/Core/Layer.cpp
GCrisp/Core/Entry.h
GCrisp/Core/GWindow.h
GCrisp/Core/Log.h
GCrisp/Core/Log.cpp
GCrisp/Core/LayerStack.h
GCrisp/Core/Layer.h
GCrisp/Core/CameraController.cpp
GCrisp/Core/UUID.cpp
GCrisp/Core/Window.cpp
GCrisp/Events/ApplicationEvent.h
GCrisp/Events/MouseEvent.h
GCrisp/Events/Event.h
GCrisp/Events/KeyEvent.h
GCrisp/Renderer/Buffer.cpp
GCrisp/Renderer/OrthoCamera.cpp
GCrisp/Renderer/Camera.h
GCrisp/Renderer/OrthoCamera.h
GCrisp/Renderer/Renderer2D.cpp
GCrisp/Renderer/Renderer.h
GCrisp/Renderer/Texture.h
GCrisp/Renderer/Renderer2D.h
GCrisp/Renderer/Texture.cpp
GCrisp/Renderer/Renderer.cpp
GCrisp/Renderer/Context.cpp
GCrisp/Renderer/VertexArray.cpp
GCrisp/Renderer/Buffer.h
GCrisp/Renderer/Context.h
GCrisp/Renderer/Shader.h
GCrisp/Renderer/VertexArray.h
GCrisp/Renderer/Shader.cpp
GCrisp/Renderer/SubTexture.h
GCrisp/Renderer/GraphicsCore.h
GCrisp/Renderer/SubTexture.cpp
GCrisp/Renderer/Utils.h
GCrisp/GCrisp.h
gcpch.cpp
gcpch.h)

add_library(GCrisp-Source STATIC ${GCRISP_SOURCE})

target_include_directories(GCrisp-Source PUBLIC .)

if(GCRISP_BUILD_DISTRIBUTABLE)
    target_compile_definitions(GCrisp-Source PUBLIC GC_DIST=1)
    set(GCRISP_PROFILING OFF)
endif()

if(GCRISP_PROFILING)
    target_compile_definitions(GCrisp-Source PUBLIC GC_PROFILING=1)
    message(STATUS "Profiling enabled")
else()
    if(GCRISP_FORCE_PROFILING)
        target_compile_definitions(GCrisp-Source PUBLIC GC_PROFILING=1)
    endif()
    target_compile_definitions(GCrisp-Source PUBLIC GC_PROFILING=0)
    message(STATUS "Profiling disabled")
endif()

target_precompile_headers(GCrisp-Source PUBLIC gcpch.h)
