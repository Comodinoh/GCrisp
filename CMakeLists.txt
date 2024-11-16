cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GCRISP_BUILD_TESTS "Build tests" ON)

set(IMGUI_DIR lib/imgui)
set(IMGUI_IMPL_OPENGL_LOADER_GLAD ON)

cmake_dependent_option(GCRISP_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_BUILD_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)

file(GLOB_RECURSE SRC_FILES src/GCrisp/*.cpp)
file(GLOB IMGUI_SRC ${IMGUI_DIR}/*.cpp)

set(IMGUI_BACKENDS ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${IMGUI_SRC} 
  ${IMGUI_BACKENDS_SRC} ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_RELEASE)
endif()

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  lib/glfw/include
  lib/imgui
  src
 )

if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows systems")

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_WIN32)
  target_include_directories(${PROJECT_NAME} PUBLIC platform/Windows)

  file(GLOB_RECURSE WINDOWS_SRC_FILES platform/Windows/*.cpp)
  
  target_sources(${PROJECT_NAME} PUBLIC ${WINDOWS_SRC_FILES})

  list(APPEND IMGUI_BACKENDS ${IMGUI_DIR}/backends/imgui_impl_win32.cpp)
elseif(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix systems")

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_POSIX)
  target_include_directories(${PROJECT_NAME} PUBLIC platform/Linux)

  file(GLOB_RECURSE LINUX_SRC_FILES platform/Linux/*.cpp)
  target_sources(${PROJECT_NAME} PUBLIC ${LINUX_SRC_FILES})
endif()

add_definitions(-DGLFW_INCLUDE_NONE)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  glad
  glfw
  spdlog::spdlog_header_only
  glm
)

target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_BACKENDS})

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)

if(GCRISP_BUILD_TESTS)
  add_subdirectory(test)
endif()

