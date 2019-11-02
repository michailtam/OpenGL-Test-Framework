#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>


bool readShaderFromFile(const std::string& fileName, std::string& shaderCode)
{
	std::ifstream file;
	file.open((fileName).c_str());
	std::string line;

	if (file.is_open()) {

		if (!file.good()) {
			std::cout << "ERROR: Shader file" << fileName << " failed to load";
			file.close();
			return false;
		}
		else {
			while (file.good()) {
				getline(file, line);
				shaderCode.append(line + "\n");
			}
			file.close();
			return true;
		}
	}
	else {
		std::cout << "ERROR: Shader file " << fileName << " could not be opened.";
		return false;
	}
}

bool checkCompileStatus(GLuint id, const std::string& type)
{
	GLint success;
	GLchar infoLog[1024];	

	if (type.compare("shader") == 0) {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			std::cout << "ERROR: " << infoLog << std::endl;
			return false;
		}
	}
	else if (type.compare("program") == 0) {
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			std::cout << "ERROR: " << infoLog << std::endl;
			return false;
		}
	}
	return true;
}

GLuint createShader(const std::string& filePath, GLuint shaderType)
{
	// Read the shader string from file
	std::string shaderSourceCode;
	if (!readShaderFromFile(filePath, shaderSourceCode)) return -1;

	// Create and compile the shader
	const GLchar* shaderSourceString[1];
	shaderSourceString[0] = shaderSourceCode.c_str();
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, shaderSourceString, nullptr);
	glCompileShader(shaderID);

	if (!checkCompileStatus(shaderID, "shader")) 
		return -1;
	else 
		return shaderID;
}

bool compileStatus(const std::string& filePath, GLuint shaderID)
{
	// Check for compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cout << "WARNING:\nShader " << filePath << " could not be compiled because: " << infoLog;
		return false;
	}
	return true;
}

GLuint compile(std::vector<GLuint> shaderIDs)
{
	GLuint programID = glCreateProgram();	// Create shader program 

	// Iterate through all shaders and attach them to the program
	for (auto shader : shaderIDs)
		glAttachShader(programID, shader);

	// Link the program and check for link errors
	glLinkProgram(programID);

	// Checks for linking errors
	if (!checkCompileStatus(programID, "program"))
		return -1;

	// Deletes all shaders
	for (auto shader : shaderIDs)
		glDeleteShader(shader);
	return programID;

}