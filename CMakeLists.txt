cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GCRISP_BUILD_TESTS "Build tests" ON)

cmake_dependent_option(GCRISP_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_BUILD_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(GCRISP_BUILD_ANDROID "Build support for Android" ON "ANDROID" OFF)

file(GLOB_RECURSE SRC_FILES src/GCrisp/*.cpp)


add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_RELEASE)
endif()

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  lib/glfw/include
  src
 )

if(GCRISP_BUILD_WIN32 OR GCRISP_BUILD_POSIX)

  file(GLOB_RECURSE OPENGL_SRC platform/Desktop/OpenGL/*.cpp)
  file(GLOB_RECURSE VULKAN_SRC platform/Desktop/Vulkan/*.cpp)
  target_sources(${PROJECT_NAME} PRIVATE ${OPENGL_SRC} ${VULKAN_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/OpenGL platform/Desktop/Vulkan)

endif()

if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows systems")

  add_definitions(-DGLFW_INCLUDE_NONE)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_WIN32)

  file(GLOB_RECURSE WIN32_SRC platform/Desktop/Win32/*.cpp)
  file(GLOB_RECURSE DIRECTX_SRC platform/Desktop/DirectX/*.cpp)

  target_sources(${PROJECT_NAME} PRIVATE ${WIN32_SRC} ${DIRECTX_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Win32 platform/Desktop/DirectX)

elseif(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix systems")

  add_definitions(-DGLFW_INCLUDE_NONE)
  file(GLOB_RECURSE LINUX_SRC platform/Desktop/Linux/*.cpp)


  target_sources(${PROJECT_NAME} PRIVATE ${LINUX_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Linux)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_POSIX)
elseif(ANDROID)
  message(STATUS "${PROJECT_NAME}: Building for Android systems")

  # Support still in progress

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_ANDROID)
endif()


target_link_libraries(${PROJECT_NAME}
  PUBLIC
  glad
  glfw
  spdlog::spdlog_header_only
  glm
)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)

if(GCRISP_BUILD_TESTS)
  add_subdirectory(test)
endif()

