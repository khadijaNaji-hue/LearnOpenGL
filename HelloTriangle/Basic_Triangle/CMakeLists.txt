cmake_minimum_required(VERSION 3.10)
project(helloWorld C CXX)

add_subdirectory(../../Libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../../Libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../../Libs/glad/include)

add_executable(helloTriangle main.cpp)
target_link_libraries(helloTriangle PRIVATE glfw glad)
