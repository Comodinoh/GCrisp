
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
  message(STATUS "Building for Windows")
endif()

if(GCRISP_BUILD_LINUX)
  message(STATUS "Building for Posix")
endif()

add_subdirectory(lib)

add_subdirectory(src)
