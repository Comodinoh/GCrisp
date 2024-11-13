file(GLOB_RECURSE SRC_FILES *.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

if(GCRISP_BUILD_WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _GCRISP_WIN32)

  list(APPEND glfw_PKG_LIBS "-lgdi32")
endif()

if(GCRISP_BUILD_POSIX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _GCRISP_POSIX)

endif()

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  ${CMAKE_SOURCE_DIR}/src
 )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  spdlog::spdlog_header_only
  glad
  glm
  glfw3)

target_precompile_headers(${PROJECT_NAME} PUBLIC gcpch.h)



