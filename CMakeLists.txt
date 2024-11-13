cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

cmake_dependent_option(GCRISP_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_BUILD_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)

if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows")
endif()

if(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix")
endif()


file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC_FILES})

if(GCRISP_BUILD_WIN32)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _GCRISP_WIN32)

  list(APPEND glfw_PKG_LIBS "-lgdi32")
endif()

if(GCRISP_BUILD_POSIX)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _GCRISP_POSIX)
endif()


add_subdirectory(lib)

target_include_directories(${CMAKE_PROJECT_NAME} 
  PUBLIC
  src
 )

target_link_libraries(${CMAKE_PROJECT_NAME}
  PUBLIC
  spdlog::spdlog_header_only
  glad
  glm
  glfw3)

target_precompile_headers(${CMAKE_PROJECT_NAME} PUBLIC src/gcpch.h)

