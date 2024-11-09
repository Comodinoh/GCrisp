cmake_minimum_required(VERSION 3.30.5)
project(gcrisp)

add_library(${PROJECT_NAME} STATIC core.c)

target_include_directories(${PROJECT_NAME} 
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR})

