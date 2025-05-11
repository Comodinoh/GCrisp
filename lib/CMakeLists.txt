add_library(GCrisp-Vendor INTERFACE)

add_subdirectory(spdlog)
add_subdirectory(glfw)
add_subdirectory(Glad)
add_subdirectory(glm EXCLUDE_FROM_ALL)
add_subdirectory(stb_impl)

function(link_vulkan)
    find_package(Vulkan ${GCRISP_VULKAN_VERSION} COMPONENTS glslc)

    if(NOT ${Vulkan_FOUND})
        include(FetchContent)
        message(FATAL_ERROR "${CMAKE_PROJECT_NAME}: Vulkan SDK not found.
    Please follow this guide https://vulkan-tutorial.com/Development_environment to setup the SDK based on your OS
    (Be sure to install glslc too)")
    else()
        target_include_directories(GCrisp-Vendor INTERFACE ${Vulkan_INCLUDE_DIRS})
        target_link_libraries(GCrisp-Vendor INTERFACE ${Vulkan_LIBRARIES})
    endif()
endfunction()

target_link_libraries(GCrisp-Vendor INTERFACE
    spdlog::spdlog
    glfw
    glad
    glm::glm
    stb
)

link_vulkan()
