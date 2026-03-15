target_sources(Vane-Platform INTERFACE Vane/Platform/DesktopInput.cpp)

target_compile_definitions(Vane-Platform INTERFACE
    VANE_DESKTOP
    VANE_OPENGL
)

target_compile_definitions(Vane-Platform INTERFACE GLFW_INCLUDE_NONE)

if(NOT MSVC)
    target_compile_options(Vane-Platform INTERFACE
        -fdiagnostics-color=always
    )
endif()

add_subdirectory(OpenGL)
target_link_libraries(Vane-Platform INTERFACE Vane-OpenGL)

if(VANE_BUILD_VULKAN)
    add_subdirectory(Vulkan)
    target_link_libraries(Vane-Platform INTERFACE Vane-Vulkan)
    target_compile_definitions(Vane-Platform INTERFACE
        VANE_VULKAN
    )
endif()
