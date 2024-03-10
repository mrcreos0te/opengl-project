#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

GLuint VAO, VBO_Positions, VBO_Colors;

void setupGeometry() {
    // Vertex data
    Vertex vertices[] = {
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}
    };

    // Create and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex Buffer Object (VBO) for positions
    glGenBuffers(1, &VBO_Positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Vertex Buffer Object (VBO) for colors
    glGenBuffers(1, &VBO_Colors);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Unbind VAO to avoid accidental changes
    glBindVertexArray(0);
}

void render() {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Unbind the VAO
    glBindVertexArray(0);
}

void cleanup() {
    // Delete VAO and VBOs
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_Positions);
    glDeleteBuffers(1, &VBO_Colors);
}

int main() {
    // GLFW and GLEW initialization code (not shown for brevity)

    // Create GLFW window, make context current, initialize GLEW (not shown for brevity)

    // Setup geometry and shaders
    setupGeometry();

    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Process input, update, etc.

        // Render the scene
        render();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup and terminate GLFW (not shown for brevity)

    return 0;
}
