#include <iostream>
#include "GL/glew.h"
#include "hello.h"

int main(int, char**) {
    std::string helloJim = generateHelloString("Jim");
    std::cout << helloJim << std::endl;

    return 0;
}