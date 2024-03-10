#ifndef TWO_D_ARRAY_H
#define TWO_D_ARRAY_H

#include <memory>
#include <vector>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

namespace MCRGraphics{
    class Line{
        public:
        Line();
        std::vector<std::pair<double,double>> vertices;
        GLuint VBO, VAO, shader;
        // Vertex Shader code
        const char* vShader = "                                                \n\
        #version 330                                                                  \n\
                                                                                    \n\
        layout (location = 1) in vec3 pos;	layout (location = 2) in vec3 pos1;		  \n\
                                                                                    \n\
        void main()                                                                   \n\
        {                                                                             \n\
            gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
        }";

        // Fragment Shader
        const char* fShader = "                                                \n\
        #version 330                                                                  \n\
                                                                                    \n\
        out vec4 colour;                                                               \n\
                                                                                    \n\
        void main()                                                                   \n\
        {                                                                             \n\
            colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
        }";

        void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
        void defineLine();
        void compileShaders();
        void draw();


    };
}

#endif