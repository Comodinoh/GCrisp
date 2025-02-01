project(stb)

add_library(${PROJECT_NAME} src/stb_image.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../stb)
