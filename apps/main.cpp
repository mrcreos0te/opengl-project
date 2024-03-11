#include <iostream>
#include <memory>
#include <string.h>
#define GLEW_STATIC
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <line.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <ranges>
#include "hello.h"

using MCRGraphics::Line;

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VBO, VAO, shader;

GLuint VBOLine, VAOLine, shaderLine;

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 1) in vec3 pos;	layout (location = 2) in vec3 pos1;		  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
uniform vec4 uColor;  // Color passed as a uniform								\n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = uColor;                                         \n\
}";

std::vector<std::string> splitString( std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    
    std::size_t pos = 0;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + 1);
    }
    
    // Add the last token
    result.push_back(input);

    return result;
}

void CreateTriangle()
{
	GLfloat vertices[] = {
		-0.20f, -0.20f, 0.0f,
		0.20f, -0.20f, 0.0f,
		0.0f, 0.20f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void CreateLine()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -2.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		-0.8f, 0.0f, 0.0f
	};

	glGenVertexArrays(1, &VAOLine);
	glBindVertexArray(VAOLine);

	glGenBuffers(1, &VBOLine);
	glBindBuffer(GL_ARRAY_BUFFER, VBOLine);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) 
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader) 
	{
		printf("Failed to create shader\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) 
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) 
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

}

int main(int, char**) {
    std::string helloJim = generateHelloString("Jim");
    std::cout << helloJim << std::endl;

    // Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	Line mcrline;

	mcrline.setStartPoint(-1.0, -1.0);
	mcrline.setEndPoint(1.0, -2.0);

	Line mcrline2;

	mcrline2.setStartPoint(-1.0, -1.0);
	mcrline2.setEndPoint(0.0, 1.0);

	std::vector<Line> lines;

	std::string path = "/home/janek/repos/opengl/opengl-project/opengl-proj/test_files/triangles4.csv";
	std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }
	auto line_view = std::ranges::istream_view<std::string>(file);
	bool verticesFound{false};

	std::vector<std::pair<double,double>> points;
	std::vector<std::pair<int,int>> conn;

    
	auto it = line_view.begin();
    auto end = line_view.end();

	while(it!=end){
		auto line = *it;
		std::cout<<*it<<std::endl;
		if(line.starts_with("#V")){
			it++;
			if((*it).starts_with("X")){
				it++;
			}
			while(!(*it).starts_with("#Conn")){
				std::cout<<"setting points for line "<<*it<<std::endl;
				std::cout<<*it<<std::endl;
				auto words = splitString(*it, ',');
				std::cout<<words[0]<<" "<<words[1]<<std::endl;
				std::pair<double,double> p(std::stod(words[0]),std::stod(words[1]));
				points.push_back(p);
				it++;
			}
			while(it!=end){
				if((*it).starts_with("#Conn")||(*it).starts_with("V")||(*it).empty()){
				it++;
				}
				else{
					std::cout<<"setting conn for line "<<*it<<std::endl;
					auto words = splitString(*it, ',');
					std::cout<<words[0]<<" "<<words[1]<<" "<<words[2]<<std::endl;
					std::pair<int,int> p(std::stoi(words[0]),std::stoi(words[1]));
					conn.push_back(p);
					std::pair<int,int> p1(std::stoi(words[1]),std::stoi(words[2]));
					conn.push_back(p1);
					std::pair<int,int> p2(std::stoi(words[2]),std::stoi(words[0]));
					conn.push_back(p2);
					it++;
				}

			}
			
		}
		it++;
	}

    
    file.close();

	for(auto pair : conn){
		Line line;
		std::cout<<std::endl;
		std::cout<<"startpoint: "<<points[pair.first].first<<" "<<points[pair.first].second<<std::endl;
		std::cout<<"endpoint: "<<points[pair.second].first<<" "<<points[pair.second].second<<std::endl;
		std::cout<<std::endl;
		line.setStartPoint(points[pair.first].first, points[pair.first].second);
		line.setEndPoint(points[pair.second].first, points[pair.second].second);
		lines.push_back(line);
	}

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// mcrline.draw();
		// mcrline2.draw();

		for(auto line : lines){
			line.draw();
		}

		glfwSwapBuffers(mainWindow);
	}

    return 0;
}

