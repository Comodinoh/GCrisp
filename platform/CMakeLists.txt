include(CMakeDependentOption)

cmake_dependent_option(VANE_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(VANE_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)
cmake_dependent_option(VANE_ANDROID "Build support for Android" ON "ANDROID" OFF)

add_library(Vane-Platform INTERFACE)

if(VANE_WIN32 OR VANE_POSIX)
  add_subdirectory(Desktop)
else()
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME}: Unsupported platform")
endif()
