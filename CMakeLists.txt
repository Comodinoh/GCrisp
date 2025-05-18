cmake_minimum_required(VERSION 3.30.5)

project(GCrisp CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GCRISP_VULKAN_VERSION 1.3.296.0)
set(OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}/${CMAKE_ARCHITECTURE}/")

option(GCRISP_BUILD_TESTS "Build tests" ON)
option(GCRISP_PROFILING "Enable profiler" ON)
option(GCRISP_FORCE_PROFILING "Force the use of the profiler regardless of build type" OFF)
option(GCRISP_BUILD_DISTRIBUTABLE "Build GCrisp as a distributable" OFF)

add_subdirectory(platform)
add_subdirectory(src)
add_subdirectory(lib)


target_link_libraries(GCrisp-Platform INTERFACE GCrisp-Vendor)
target_link_libraries(GCrisp-Source PUBLIC GCrisp-Platform)

if(MSVC)
  target_compile_options(GCrisp-Source PRIVATE /W4 /Wall /sdl /external:anglebrackets /external:W2 /fsanitizer=address)
else()
  target_compile_options(GCrisp-Source PRIVATE -Wall -Wextra -Wpedantic )
endif()

if(GCRISP_BUILD_TESTS)
    add_subdirectory(test)
endif()
