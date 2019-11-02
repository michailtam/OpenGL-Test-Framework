#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

// GLM math library
#define GLM_FORCE_SWIZZLE
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

void createVertex(std::vector<float> positions, std::vector<float> colors, std::vector<Vertex>& vertices)
{
	if (positions.size() == 0) return;

	unsigned int sizePos = positions.size();
	unsigned int sizeCol = colors.size();
	unsigned int sizeVertices = positions.size() / 3;
	unsigned int idx = 0;

	for (unsigned int i=0; i <sizeVertices; i++)
	{
		Vertex vert;
		for (unsigned int j=0; j<3; j++) 
		{
			vert.position[j] = positions[idx];
			if (idx < sizeCol)
				vert.color[j] = colors[idx];
			else
				vert.color[j] = 0.0f;
			idx++;
		}
		vertices.push_back(vert);
	}
}

void tokenize(const std::string& str, const std::string& delimiter, std::vector<std::string>& tokens)
{
	std::string s = str;
	size_t pos = 0;
	std::string token;
	float value = -1;
	std::string::size_type size = -1;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, s.find(delimiter));
		s.erase(0, pos + delimiter.length());
		tokens.push_back(token);
	}
}

bool readData(const std::string& path, std::vector<float>& data)
{
	try
	{
		// Reads the file line by line and performs data extraction
		std::string str;
		bool endFile = false;
		std::ifstream input;
		input.open(path);
		std::vector<std::string> tokens;
		std::string::size_type size;
		float value = -1;

		while (std::getline(input, str))
		{
			if (str.compare("") == 0) continue;

			tokenize(str, ",", tokens);	// Tokenizes the string using a delimiter
			for (auto token : tokens) {
				float value = std::stof(token, &size);
				data.push_back(value);
			}
			tokens.clear();
		}
		input.close();
	}
	catch (std::exception e) {
		std::cout << "File Opening Error" << e.what() << std::endl;
		return false;
	}
	return true;
}

