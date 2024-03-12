cmake_minimum_required(VERSION 3.28)

project(GraphicLearn VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(glad)
add_subdirectory(glfw)

