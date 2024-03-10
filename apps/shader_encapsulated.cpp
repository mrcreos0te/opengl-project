#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
public:
    Shader(const char* vertexSource, const char* fragmentSource) {
        // Create the vertex shader
        vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);

        // Create the fragment shader
        fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);

        // Create the shader program
        shaderProgram = createShaderProgram(vertexShader, fragmentShader);
    }

    void use() const {
        glUseProgram(shaderProgram);
    }

    ~Shader() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
    }

private:
    GLuint vertexShader, fragmentShader, shaderProgram;

    GLuint createShader(GLenum shaderType, const char* source) const {
        GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        checkCompileErrors(shader, "SHADER");

        return shader;
    }

    GLuint createShaderProgram(GLuint vertex, GLuint fragment) const {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);
        checkCompileErrors(program, "PROGRAM");

        return program;
    }

    void checkCompileErrors(GLuint shader, const char* type) const {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
};

class Triangle {
public:
    Triangle() {
        // Vertex data
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,  // Position of the first vertex
            1.0f, 0.0f, 0.0f,    // Color of the first vertex (red)

            0.5f, -0.5f, 0.0f,   // Position of the second vertex
            0.0f, 1.0f, 0.0f,    // Color of the second vertex (green)

            0.0f, 0.5f, 0.0f,    // Position of the third vertex
            0.0f, 0.0f, 1.0f     // Color of the third vertex (blue)
        };

        // Vertex buffer object (VBO)
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Vertex array object (VAO)
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        // Set up position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        // Set up color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render() const {
        // Bind the VAO
        glBindVertexArray(VAO);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Unbind the VAO
        glBindVertexArray(0);
    }

    ~Triangle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

private:
    GLuint VBO, VAO;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set GLFW to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Colored Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Set the viewport size and callback function for resizing
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Vertex shader
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPosition;
        layout (location = 1) in vec3 aColor;

        out vec3 color;

        void main()
        {
            gl_Position = vec4(aPosition, 1.0);
            color = aColor;
        }
    )";

    // Fragment shader
    const char* fragmentShaderSource = R"(
        #version 330 core
        in vec3 color;

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(color, 1.0);
        }
    )";

    // Create shader
    Shader shader(vertexShaderSource, fragmentShaderSource);

    Triangle myTriangle;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Process input, render, etc.

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        shader.use();

        // Render the triangle
        myTriangle.render();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    return 0;
}
