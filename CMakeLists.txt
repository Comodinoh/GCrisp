cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always")

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

  file(GLOB_RECURSE COMMONS_SRC platform/Desktop/Commons/*.cpp)
  target_sources(${PROJECT_NAME} PRIVATE ${COMMONS_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Commons)
  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_DESKTOP)
endif()

if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows systems")

  add_definitions(-DGLFW_INCLUDE_NONE)


  file(GLOB_RECURSE WIN32_SRC platform/Desktop/Win32/*.cpp)

  target_sources(${PROJECT_NAME} PRIVATE ${WIN32_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Win32)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_WIN32)
elseif(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix systems")

  add_definitions(-DGLFW_INCLUDE_NONE)
  file(GLOB_RECURSE LINUX_SRC platform/Desktop/Linux/*.cpp)


  target_sources(${PROJECT_NAME} PRIVATE ${LINUX_SRC})
  target_include_directories(${PROJECT_NAME} PRIVATE platform/Desktop/Linux)

  target_compile_definitions(${PROJECT_NAME} PUBLIC GC_POSIX)
elseif(ANDROID)
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

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)

if(GCRISP_BUILD_TESTS)
  add_subdirectory(test)
endif()

