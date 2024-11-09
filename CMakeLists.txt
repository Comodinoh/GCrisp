cmake_minimum_required(VERSION 3.30.5)
project(gcrisp)



file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  src)

add_subdirectory(lib)



