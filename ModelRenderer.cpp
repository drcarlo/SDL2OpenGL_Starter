#include "ModelRenderer.h"


ModelRenderer::ModelRenderer(GE::Camera* c) : camera(c)
{
	shaders = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	if (!shaders->init()) {
		std::cout << "Could not init model renderer shaders!" << std::endl;
		return;
	}
}

ModelRenderer::~ModelRenderer() {
	delete shaders;
}

void ModelRenderer::drawModel(Model* model)
{
	shaders->bind();
	// Calculate the transformation matrix for the object
	glm::vec3 position(5, 0, 5), scale(1, 1, 1);
	glm::mat4 transformationMat = glm::mat4(1.0f);
	transformationMat = glm::translate(transformationMat, glm::vec3(position.x, position.y, position.z));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transformationMat = glm::rotate(transformationMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transformationMat = glm::scale(transformationMat, scale);


	glm::mat4 projectionMat = camera->getProjectionMatrix();

	GLCALL(glUniformMatrix4fv(shaders->getLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(transformationMat)));
	GLCALL(glUniformMatrix4fv(shaders->getLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix())));
	GLCALL(glUniformMatrix4fv(shaders->getLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix())));



	unsigned int vao = model->getVAOs()[0];
	unsigned int elementCount = model->getIndexCounts()[0];

	Texture* texture = model->getTextures()[0];
	GLCALL(glBindVertexArray(vao));
		GLCALL(glUniform1i(shaders->getLocation("textureSampler"), 0));
		GLCALL(glActiveTexture(GL_TEXTURE0));
		GLCALL(glBindTexture(GL_TEXTURE_2D, texture->getTextureId()));

		GLCALL(glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr));

		GLCALL(glBindVertexArray(NULL));

	shaders->unbind();
}
