cmake_minimum_required(VERSION 3.30.5)

project(gcrisp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GC_ENABLE_ASSERTS "Enable assert checking" OFF)

cmake_dependent_option(GCRISP_BUILD_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GCRISP_BUILD_POSIX "Build support for Posix/Linux" ON "UNIX;NOT APPLE" OFF)

file(GLOB_RECURSE SRC_FILES src/GCrisp/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<CONFIG:Debug>:_GCRISP_DEBUG>
    $<$<CONFIG:Release>:_GCRISP_RELEASE>

    $<$<CONFIG:RelWithDebInfo>:_GCRISP_DEBUG>
    $<$<CONFIG:MinSizeRel>:_GCRISP_RELEASE>
)

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  src
 )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  spdlog::spdlog_header_only
  glad
  glm
  glfw)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)


if(GCRISP_BUILD_WIN32)
  message(STATUS "${PROJECT_NAME}: Building for Windows systems")

  target_compile_definitions(${PROJECT_NAME} PUBLIC _GCRISP_WIN32)
  target_include_directories(${PROJECT_NAME} PUBLIC platform/Windows)

  file(GLOB_RECURSE WINDOWS_SRC_FILES platform/Windows/*.cpp)
  
  target_sources(${PROJECT_NAME} PRIVATE ${WINDOWS_SRC_FILES})
endif()

if(GCRISP_BUILD_POSIX)
  message(STATUS "${PROJECT_NAME}: Building for Posix systems")

  target_compile_definitions(${PROJECT_NAME} PUBLIC _GCRISP_POSIX)
  target_include_directories(${PROJECT_NAME} PUBLIC platform/Linux)

  file(GLOB_RECURSE LINUX_SRC_FILES platform/Linux/*.cpp)
  target_sources(${PROJECT_NAME} PUBLIC ${LINUX_SRC_FILES})
endif()


