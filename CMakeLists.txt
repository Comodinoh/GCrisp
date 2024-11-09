cmake_minimum_required(VERSION 3.30.5)
project(gcrisp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  include
  PUBLIC
  lib/SDL/include)

target_link_directories(${PROJECT_NAME}
  PRIVATE
  lib/SDL/src
  )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  SDL3)

add_subdirectory(lib)



