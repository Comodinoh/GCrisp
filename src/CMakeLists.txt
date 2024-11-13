file(GLOB_RECURSE SRC_FILES *.cpp)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC_FILES})

if(GCRISP_BUILD_WIN32)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _GCRISP_WIN32)

  list(APPEND glfw_PKG_LIBS "-lgdi32")
endif()

if(GCRISP_BUILD_POSIX)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE _GCRISP_POSIX)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} 
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
 )

target_link_libraries(${CMAKE_PROJECT_NAME}
  PUBLIC
  spdlog::spdlog_header_only
  glad
  glm
  glfw3)

target_precompile_headers(${CMAKE_PROJECT_NAME} PUBLIC gcpch.h)




