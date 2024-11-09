cmake_minimum_required(VERSION 3.30.5)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(gcrisp STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  src)
target_link_directories(${PROJECT_NAME} PRIVATE src)

