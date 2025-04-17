cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GCRISP_VULKAN_VERSION 1.3.296.0)


include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GCRISP_BUILD_TESTS "Build tests" ON)
option(GCRISP_PROFILING "Enable profiler" ON)
option(GCRISP_FORCE_PROFILING "Force the use of the profiler regardless of build type" OFF)
option(GCRISP_BUILD_DISTRIBUTABLE "Build GCrisp as a distributable" OFF)

cmake_dependent_option(GCRISP_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_BUILD_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(GCRISP_BUILD_ANDROID "Build support for Android" ON "ANDROID" OFF)

file(GLOB_RECURSE SRC_FILES src/GCrisp/*.cpp src/GCrisp/*.h)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} "src/GCrisp/Renderer/VertexArray.cpp" "src/GCrisp/Core/Window.cpp" "src/GCrisp/Renderer/Texture.cpp" "src/GCrisp/Renderer/Context.cpp"
        src/GCrisp/Renderer/Shader.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
  set(GCRISP_BUILD_DISTRIBUTABLE ON)
endif()

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  lib/glfw/include
  src
 )

function(link_vulkan)
  find_package(Vulkan ${GCRISP_VULKAN_VERSION} COMPONENTS glslc)

  if(NOT ${Vulkan_FOUND})
    include(FetchContent)
    message(FATAL_ERROR "${PROJECT_NAME}: Vulkan SDK not found.
    Please follow this guide https://vulkan-tutorial.com/Development_environment to setup the SDK based on your OS 
    (Be sure to install glslc too)")
  else()
    target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})
  endif()
endfunction()

if(GCRISP_BUILD_WIN32 OR GCRISP_BUILD_POSIX)
  link_vulkan()

  add_definitions(-DGLFW_INCLUDE_NONE)

  file(GLOB_RECURSE COMMONS_SRC platform/Desktop/Commons/*.cpp)
  target_sources(${PROJECT_NAME} PRIVATE ${COMMONS_SRC}) 
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Commons)
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_DESKTOP)

   target_compile_definitions(${PROJECT_NAME} PUBLIC GC_VULKAN GC_OPENGL)
endif()

if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows systems")

  file(GLOB_RECURSE WIN32_SRC platform/Desktop/Win32/*.cpp)

  target_sources(${PROJECT_NAME} PRIVATE ${WIN32_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Win32)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_WIN32 GC_DIRECTX)
elseif(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix systems")
  
  set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always")

  file(GLOB_RECURSE LINUX_SRC platform/Desktop/Linux/*.cpp)

  target_sources(${PROJECT_NAME} PRIVATE ${LINUX_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Linux)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_POSIX)
elseif(GCRISP_BUILD_ANDROID)
  message(FATAL_ERROR "${PROJECT_NAME}: Building for Android systems isn't supported yet!")
  # Support still in progress
endif()


target_link_libraries(${PROJECT_NAME}
  PUBLIC
  glad
  glfw
  spdlog::spdlog_header_only
  glm::glm-header-only
  stb
)

if(GCRISP_BUILD_DISTRIBUTABLE)
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_DIST=1)
  set(GCRISP_PROFILING OFF)
endif()

if(GCRISP_PROFILING)
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_PROFILING=1)
  message(STATUS "Profiling enabled")
else()
  if(GCRISP_FORCE_PROFILING)
    target_compile_definitions(${PROJECT_NAME} PUBLIC GC_PROFILING=1)
  endif()
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_PROFILING=0)
  message(STATUS "Profiling disabled")
endif()

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)


if(GCRISP_BUILD_TESTS)
  add_subdirectory(test)
endif()