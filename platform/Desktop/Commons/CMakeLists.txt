set(GCRISP_DESKTOP_COMMON_SOURCE
    GCrisp/Platform/OpenGL/GGLAPI.cpp
    GCrisp/Platform/OpenGL/GGLAPI.h
    GCrisp/Platform/OpenGL/GLBuffer.cpp
    GCrisp/Platform/OpenGL/GLBuffer.h
    GCrisp/Platform/OpenGL/GLContext.cpp
    GCrisp/Platform/OpenGL/GLContext.h
    GCrisp/Platform/OpenGL/GLCreator.cpp
    GCrisp/Platform/OpenGL/GLCreator.h
    GCrisp/Platform/OpenGL/GLShader.cpp
    GCrisp/Platform/OpenGL/GLShader.h
    GCrisp/Platform/OpenGL/GLTexture.cpp
    GCrisp/Platform/OpenGL/GLTexture.h
    GCrisp/Platform/OpenGL/GLVertexArray.cpp
    GCrisp/Platform/OpenGL/GLVertexArray.h
    GCrisp/Platform/OpenGL/GLWindow.cpp
    GCrisp/Platform/OpenGL/GLWindow.h
    #GCrisp/Platform/Vulkan/VulkanAPI.cpp
    #GCrisp/Platform/Vulkan/VulkanAPI.h
    #GCrisp/Platform/Vulkan/VulkanBuffer.cpp
    #GCrisp/Platform/Vulkan/VulkanBuffer.h
    GCrisp/Platform/Vulkan/VKContext.cpp
    GCrisp/Platform/Vulkan/VKContext.h
    GCrisp/Platform/Vulkan/VKCreator.cpp
    GCrisp/Platform/Vulkan/VKCreator.h
    #GCrisp/Platform/Vulkan/VulkanShader.cpp
    #GCrisp/Platform/Vulkan/VulkanShader.h
    #GCrisp/Platform/Vulkan/VulkanTexture.cpp
    #GCrisp/Platform/Vulkan/VulkanTexture.h
    #GCrisp/Platform/Vulkan/VulkanVertexArray.cpp
    #GCrisp/Platform/Vulkan/VulkanVertexArray.h
    GCrisp/Platform/Vulkan/VKWindow.cpp
    GCrisp/Platform/Vulkan/VKWindow.h
    GCrisp/Platform/DesktopInput.cpp
)

target_sources(GCrisp-Platform INTERFACE ${GCRISP_DESKTOP_COMMON_SOURCE})

target_include_directories(GCrisp-Platform INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(GCrisp-Platform INTERFACE
    GC_DESKTOP
    GC_OPENGL
    GC_VULKAN)

target_compile_definitions(GCrisp-Platform INTERFACE GLFW_INCLUDE_NONE)

if(NOT MSVC)
    target_compile_options(GCrisp-Platform INTERFACE
        -fdiagnostics-color=always
    )
endif()
