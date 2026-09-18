cmake_minimum_required(VERSION 3.10)
project(Shaders_CH C CXX)

add_subdirectory(../../Libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../../Libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../../Libs/glad/include)


add_executable(Shaders_CH main.cpp shader.cpp)
target_link_libraries(Shaders_CH PRIVATE glfw glad)
