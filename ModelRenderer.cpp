#include "ModelRenderer.h"


ModelRenderer::ModelRenderer(GE::Camera* c) : camera(c)
{
	// Write code here to load a vertex and a fragment shader.
	// Create and link both shaders into a new gl program.
	// Make sure to keep track of the locations of any uniforms
	// or inputs.

	// Vertex Shader
	programId = glCreateProgram();

	const char* shaderSource =
		"Source Code for your shaders!\n"
		"Again, we should probably load shaders from files\n"
		"\n"
		"As this is prone to errors and will get difficult to manage;\n"
		"\n";

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char**)&shaderSource, nullptr);
	glCompileShader(vertexShader);
	int success = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "[ERROR] Could not compile vertex shader in Model Renderer!" << std::endl;
		return;
	}
	glAttachShader(programId, vertexShader);

	// Fragment Shader
	shaderSource =
		"Source Code for your shaders!\n"
		"\n";

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char**)&shaderSource, nullptr);
	glCompileShader(fragmentShader);
	success = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		printf("[ERROR] Could not compile fragment shader in Model Renderer! \n");
		return;
	}
	glAttachShader(programId, fragmentShader);

	// Some code to link, compile and validate you shaders 

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void ModelRenderer::drawModel(Model* model)
{

	glUseProgram(programId);

	glm::vec3 rotation(0, 0, 0), translation(0, 0, 0), scale(1, 1, 1);

	// Create and manipulate the Model Matrix
	glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix
	modelMatrix = glm::rotate(modelMatrix, rotation.x * 180.0f / pi, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y * 180.0f / pi, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z * 180.0f / pi, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, scale);

	// Set Uniforms/Attributes
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

	// Vertex positions
	glEnableVertexAttribArray(vertexPositionLocation);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GE::Vertex), nullptr);
	// UV coordinates
	glEnableVertexAttribArray(uvLocation);
	//glVertexAttribPointer(uvLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GE::Vertex), (void*)offsetof(GE::Vertex, u));


	// Texture
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureSamplerLocation, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	// Drawing Function
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

	// Remember to clean up and deselect everything! 
	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
	glUseProgram(NULL);
}
