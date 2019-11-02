#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.h"
#include "models.h"

#define SHADER_PATH "./shaders/"
#define DATA_PATH "./models/"


// Screen dimensions
const unsigned int INIT_SCEENE_WIDTH = 1920;
const unsigned int INIT_SCEENE_HEIGHT = 1080;

float sceenWidth = 1920.0;
float sceenHeight = 1080.0;

GLuint vao;
GLuint prog;

// Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


void createShaders()
{
	GLuint vertID = createShader("./shaders/test.vert", GL_VERTEX_SHADER);
	if (vertID == -1) exit(EXIT_FAILURE);
	GLuint fragID = createShader("./shaders/test.frag", GL_FRAGMENT_SHADER);
	if (fragID == -1) exit(EXIT_FAILURE);
	std::vector<GLuint> shaderIDs;
	shaderIDs.push_back(vertID);
	shaderIDs.push_back(fragID);
	prog = compile(shaderIDs);
	if (prog == -1)
		exit(EXIT_FAILURE);
}

void setupModelData()
{
	std::vector<float> positions;
	std::vector<float> colors;
	std::vector<Vertex> vertices;
	readData(DATA_PATH + std::string("vertices.data"), positions);
	readData(DATA_PATH + std::string("colors.col"), colors);
	createVertex(positions, colors, vertices);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		GLuint vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	}
}


int main()
{
	// Setup the GLFW context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(INIT_SCEENE_WIDTH, INIT_SCEENE_HEIGHT, "OpenGL Test Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	setupModelData();
	createShaders();

	// Rendering loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(prog);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
	return EXIT_SUCCESS;
}


// CALLBACK FUNCTIONS

// Process all keys (pressed/released)
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Whenever the window size changed this callback function gets executed
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	sceenWidth = (float)width;
	sceenHeight = (float)height;
	glViewport(0, 0, width, height);
}