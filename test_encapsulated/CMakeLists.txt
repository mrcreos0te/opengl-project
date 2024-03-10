# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(encapsulate)

add_executable(encapsulate encapsulate.cpp)


# We need hello.h and the hello library
target_link_libraries(encapsulate
    PUBLIC OpenGL::GL
    PUBLIC GLEW::GLEW
    PUBLIC glfw
    PUBLIC glm)

#target_link_libraries(main GLEW::GLEW)

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(encapsulate PUBLIC cxx_std_20)