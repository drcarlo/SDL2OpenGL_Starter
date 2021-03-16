#include "Utils.h"

std::string utils::readFile(const std::string& path)
{
	std::ifstream shaderFile(path);
	std::stringstream shaderSource;


	std::string line;
	if (shaderFile.is_open()) {
		while (std::getline(shaderFile, line)) {
			shaderSource << line << std::endl;
		}
		shaderFile.close();
	}
	else {
		printf("[ERROR] Could not open file: %s \n", path.c_str());
	}
	return shaderSource.str();
}

void utils::printShaderError(unsigned int shaderLocation)
{
	int logLength;
	glGetShaderiv(shaderLocation, GL_INFO_LOG_LENGTH, &logLength);
	
	char* logMessage = new char[(size_t)(logLength + 1)];
	glGetShaderInfoLog(shaderLocation, logLength, &logLength, &logMessage[0]);
	std::cout << logMessage << std::endl;
	delete[] logMessage;
}
