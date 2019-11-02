#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


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

