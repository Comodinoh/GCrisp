cmake_minimum_required(VERSION 3.30.5)
project(gcrisp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  src
  PUBLIC
  lib/SDL/include
 )

target_link_directories(${PROJECT_NAME}
  PRIVATE
  lib/SDL/src
  )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  spdlog::spdlog_header_only
  SDL3::SDL3
  glad
  glm)

target_precompile_headers(${PROJECT_NAME} PUBLIC src/gcpch.h)




