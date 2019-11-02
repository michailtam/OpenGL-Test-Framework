#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.h"
#include "models.h"

#define SHADER_PATH "./shaders/"
#define DATA_PATH "./models/"

// Screen dimensions
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

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
	readData(DATA_PATH + std::string("vertices.data"), positions);
	readData(DATA_PATH + std::string("colors.col"), colors);

	GLuint vbo[2];
	glGenBuffers(2, vbo);
	GLuint positionID = vbo[0];
	GLuint colorID = vbo[1];

	glBindBuffer(GL_ARRAY_BUFFER, positionID);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positions.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorID);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, positionID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, colorID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}


int main()
{
	// Setup the GLFW context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Test Window", NULL, NULL);
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
	glViewport(0, 0, width, height);
}