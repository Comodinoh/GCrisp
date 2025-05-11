include(CMakeDependentOption)

cmake_dependent_option(GCRISP_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(GCRISP_ANDROID "Build support for Android" ON "ANDROID" OFF)

add_library(GCrisp-Platform INTERFACE)

if(GCRISP_WIN32 OR GCRISP_POSIX)
  add_subdirectory(Desktop)
else()
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME}: Unsupported platform")
endif()
