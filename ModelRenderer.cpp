#include "ModelRenderer.h"


ModelRenderer::ModelRenderer(GE::Camera* c) : camera(c)
{
	// Write code here to load a vertex and a fragment shader.
	// Create and link both shaders into a new gl program.
	// Make sure to keep track of the locations of any uniforms
	// or inputs.

	// Vertex Shader
	programId = glCreateProgram();

	std::string vertexShaderSource = utils::readFile("resources/shaders/vertex_shader.glsl");
	std::string fragmentShaderSource = utils::readFile("resources/shaders/fragment_shader.glsl");

	const char* shaderSource = vertexShaderSource.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSource, nullptr);
	glCompileShader(vertexShader);
	int success = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cerr << "[ERROR] Could not compile vertex shader in Model Renderer!" << std::endl;
		utils::printShaderError(vertexShader);
		return;
	}

	glAttachShader(programId, vertexShader);

	// Fragment Shader
	shaderSource = fragmentShaderSource.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&shaderSource, nullptr);
	glCompileShader(fragmentShader);
	success = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cerr << "[ERROR] Could not compile fragment shader in Model Renderer!" << std::endl;
		utils::printShaderError(fragmentShader);
		return;
	}
	glAttachShader(programId, fragmentShader);

	// Some code to link, compile and validate you shaders 
	glLinkProgram(programId);
	success = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		std::cerr << "[ERROR] Could not link shader in Model Renderer! \n" << std::endl;
		return;
	}

	glValidateProgram(programId);
	success = GL_FALSE;
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
	if (success != GL_TRUE) {
		std::cerr << "[ERROR] Could not validate shader in Model Renderer! \n" << std::endl;
		return;
	}

	glDetachShader(programId, vertexShader);
	glDetachShader(programId, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);


	glUseProgram(programId);
	
	// Get uniforms and attributes

}


void ModelRenderer::drawModel(Model* model)
{
	glUseProgram(programId);
	// Calculate the transformation matrix for the object
	glm::vec3 position(0, 0, 0), rotation(0, -120, 0), scale(1, 1, 1);
	glm::mat4 transformationMat = glm::mat4(1.0f);
	transformationMat = glm::translate(transformationMat, glm::vec3(position.x, position.y, position.z));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transformationMat = glm::scale(transformationMat, scale);

	// Get view and projection matrices
	glm::mat4 viewMat = camera->getViewMatrix();
	glm::mat4 projectionMat = camera->getProjectionMatrix();

	// Select the program in the rendering context

	// Set the shader uniforms
	GLCALL(glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformationMat)));
	GLCALL(glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMat)));
	GLCALL(glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMat)));

	// Bind vertex or buffer arrays
	glUseProgram(0);
}
