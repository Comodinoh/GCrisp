target_sources(GCrisp-Platform INTERFACE GCrisp/Platform/DesktopInput.cpp)

target_compile_definitions(GCrisp-Platform INTERFACE
    GC_DESKTOP
    GC_OPENGL
)

target_compile_definitions(GCrisp-Platform INTERFACE GLFW_INCLUDE_NONE)

if(NOT MSVC)
    target_compile_options(GCrisp-Platform INTERFACE
        -fdiagnostics-color=always
    )
endif()

add_subdirectory(OpenGL)
target_link_libraries(GCrisp-Platform INTERFACE GCrisp-OpenGL)

if(GCRISP_BUILD_VULKAN)
    add_subdirectory(Vulkan)
    target_link_libraries(GCrisp-Platform INTERFACE GCrisp-Vulkan)
    target_compile_definitions(GCrisp-Platform INTERFACE
        GC_VULKAN
    )
endif()
