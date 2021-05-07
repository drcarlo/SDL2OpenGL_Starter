#pragma once

#include <string>
#include <GL/glew.h>
#include "Utils.h"

class Shader
{
public:
	Shader(const std::string& VertexShaderfile, const std::string& FragmentShaderfile);
	~Shader() { glDeleteProgram(programID); }
	bool init();

	int getLocation(const std::string& location);
	void bind() { GLCALL(glUseProgram(programID)); }
	void unbind() { GLCALL(glUseProgram(NULL)); }

private:
	unsigned int programID;
	std::string vertexShaderFile, fragmentShaderFile;
};