cmake_minimum_required(VERSION 3.10)
project(Pinwheel_Rotation C CXX)

add_subdirectory(../../Libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../../Libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../../Libs/glad/include)


add_executable(Pinwheel_Rotation main.cpp shader.cpp)
target_link_libraries(Pinwheel_Rotation PRIVATE glfw glad)
