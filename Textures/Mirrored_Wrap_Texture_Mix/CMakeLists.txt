cmake_minimum_required(VERSION 3.10)
project(Mirrored_Wrap_Texture_Mix C CXX)

add_subdirectory(../../Libs/glfw ${CMAKE_BINARY_DIR}/glfw)

add_library(glad ../../Libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ../../Libs/glad/include)


add_executable(Mirrored_Wrap_Texture_Mix main.cpp shader.cpp ../../Libs/stb/stb_image_impl.cpp)
target_include_directories(Mirrored_Wrap_Texture_Mix PRIVATE ../../Libs/stb)
target_link_libraries(Mirrored_Wrap_Texture_Mix PRIVATE glfw glad)
