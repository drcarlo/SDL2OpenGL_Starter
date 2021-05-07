#include "Shader.h"

Shader::Shader(const std::string& VertexShaderfile, const std::string& FragmentShaderfile)

	: vertexShaderFile(VertexShaderfile)
	, fragmentShaderFile(FragmentShaderfile)
{
}

bool Shader::init()
{
	std::string vertexSource = utils::readFile(vertexShaderFile);
	std::string fragmentSource = utils::readFile(fragmentShaderFile);
	programID = glCreateProgram();

	const char* shaderSource = vertexSource.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	glCompileShader(vertexShader);
	int success = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cerr << "[ERROR] Could not compile vertex shader in Shader!" << std::endl;
		utils::printShaderError(vertexShader);
		return false;
	}
	glAttachShader(programID, vertexShader);


	// Fragment Shader
	shaderSource = fragmentSource.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&shaderSource, nullptr);
	glCompileShader(fragmentShader);
	success = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cerr << "[ERROR] Could not compile fragment shader in Shader!" << std::endl;
		utils::printShaderError(fragmentShader);
		return false;
	}
	glAttachShader(programID, fragmentShader);

	// Some code to link, compile and validate you shaders 
	glLinkProgram(programID);
	success = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		std::cerr << "[ERROR] Could not link shader in Model Renderer! \n" << std::endl;
		return false;
	}

	glValidateProgram(programID);
	success = GL_FALSE;
	glGetProgramiv(programID, GL_VALIDATE_STATUS, &success);
	if (success != GL_TRUE) {
		std::cerr << "[ERROR] Could not validate shader in Model Renderer! \n" << std::endl;
		return false;
	}
	glDetachShader(programID, vertexShader);
	glDetachShader(programID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

int Shader::getLocation(const std::string& location)
{
	return glGetUniformLocation(programID, location.c_str());
}