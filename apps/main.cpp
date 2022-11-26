#include <iostream>
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "hello.h"

int main(int, char**) {
    std::string helloJim = generateHelloString("Jim");
    std::cout << helloJim << std::endl;

    glewInit();

    return 0;
}