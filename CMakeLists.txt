# version 3.11 or later of CMake needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(
    VscodeCmakeHello
    VERSION 0.1
    DESCRIPTION "Small CMake example built with VSCode")

#find_path(GLEW_INCLUDE_DIR GL/glew.h)
#find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)

find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_subdirectory(hello)   # look in hello subdirectory for CMakeLists.txt to process
add_subdirectory(apps)    # look in apps subdirectory for CMakeLists.txt to process